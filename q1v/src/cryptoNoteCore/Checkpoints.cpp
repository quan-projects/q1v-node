// Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018, The Niobio Cash developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#include "Checkpoints.h"
#include "../CryptoNoteConfig.h"
#include "common/StringTools.h"
#include "common/DnsTools.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <boost/algorithm/string.hpp>

using namespace Logging;

namespace Q1v {
    //---------------------------------------------------------------------------
    Checkpoints::Checkpoints(Logging::ILogger &log) : logger(log, "checkpoints") {}

    //---------------------------------------------------------------------------
    bool Checkpoints::add_checkpoint(uint64_t height, const std::string &hash_str) {
        Crypto::Hash h = NULL_HASH;
        if (!Common::podFromHex(hash_str, h)) {
            logger(WARNING) << "Wrong hash in checkpoint for height " << height;
            return false;
        }
        if (!(0 == m_points.count(height))) {
            logger(WARNING) << "Checkpoint already exists.";
            return false;
        }

        m_points[height] = h;

        return true;
    }

    //---------------------------------------------------------------------------
    bool Checkpoints::is_in_checkpoint_zone(uint64_t height) const {
        return !m_points.empty() && (height <= (--m_points.end())->first);
    }

    //---------------------------------------------------------------------------
    bool Checkpoints::check_block(uint64_t height, const Crypto::Hash &h, bool &is_a_checkpoint) const {
        auto it = m_points.find(height);
        is_a_checkpoint = it != m_points.end();
        if (!is_a_checkpoint)
            return true;

        if (it->second == h) {
            logger(Logging::INFO, Logging::GREEN) << "CHECKPOINT PASSED FOR HEIGHT " << height << " " << h;
            return true;
        } else {
            logger(Logging::ERROR) << "CHECKPOINT FAILED FOR HEIGHT " << height << ". EXPECTED HASH: " << it->second
                                   << ", FETCHED HASH: " << h;
            return false;
        }
    }

    //---------------------------------------------------------------------------
    bool Checkpoints::check_block(uint64_t height, const Crypto::Hash &h) const {
        bool ignored;
        return check_block(height, h, ignored);
    }

    //---------------------------------------------------------------------------
    bool Checkpoints::is_alternative_block_allowed(uint64_t blockchain_height, uint64_t block_height) const {
        if (0 == block_height) return false;
        if (block_height < blockchain_height - Q1v::parameters::CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW &&
            !is_in_checkpoint_zone(block_height)) {
            logger(Logging::ERROR, Logging::BRIGHT_WHITE) << "An attempt of too deep reorganization: "
                                                          << blockchain_height - block_height << ", BLOCK REJECTED";
            return false;
        }
        auto it = m_points.upper_bound(blockchain_height);
        // Is blockchain_height before the first checkpoint?
        if (it == m_points.begin())
            return true;

        --it;
        uint32_t checkpoint_height = it->first;
        return checkpoint_height < block_height;
    }

    std::vector<uint64_t> Checkpoints::getCheckpointHeights() const {
        std::vector<uint64_t> checkpointHeights;
        checkpointHeights.reserve(m_points.size());
        for (const auto &it: m_points) {
            checkpointHeights.push_back(it.first);
        }

        return checkpointHeights;
    }

    bool Checkpoints::load_checkpoints_from_dns() {
        // better code from Karbo developers
        std::string domain("checkpoints.niobiocash.money");
        std::vector<std::string> records;

        logger(Logging::INFO) << "Fetching DNS checkpoint records.";

        if (!Common::fetch_dns_txt(domain, records)) {
            logger(Logging::INFO) << "Failed to lookup DNS checkpoint records";
        }

        for (const auto &record: records) {
            uint64_t height;
            Crypto::Hash hash = NULL_HASH;
            std::stringstream ss;
            size_t del = record.find_first_of(':');
            std::string height_str = record.substr(0, del), hash_str = record.substr(del + 1, 64);
            ss.str(height_str);
            ss >> height;
            char c;
            if (del == std::string::npos) continue;
            if ((ss.fail() || ss.get(c)) || !Common::podFromHex(hash_str, hash)) {
                logger(Logging::INFO) << "Failed to parse DNS checkpoint record: " << record;
                continue;
            }
            if (0 == m_points.count(height)) {
                add_checkpoint(height, hash_str);
            }
        }
        return true;
    }
}
