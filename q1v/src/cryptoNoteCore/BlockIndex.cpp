/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#include "BlockIndex.h"

#include <boost/utility/value_init.hpp>

#include "CryptoNoteSerialization.h"
#include "serialization/SerializationOverloads.h"

namespace Q1v {
    Crypto::Hash BlockIndex::getBlockId(uint32_t height) const {
        assert(height < m_container.size());

        return m_container[static_cast<size_t>(height)];
    }

    std::vector<Crypto::Hash> BlockIndex::getBlockIds(uint32_t startBlockIndex, uint32_t maxCount) const {
        std::vector<Crypto::Hash> result;
        if (startBlockIndex >= m_container.size()) {
            return result;
        }

        size_t count = std::min(static_cast<size_t>(maxCount),
                                m_container.size() - static_cast<size_t>(startBlockIndex));
        result.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            result.push_back(m_container[startBlockIndex + i]);
        }

        return result;
    }

    bool BlockIndex::findSupplement(const std::vector<Crypto::Hash> &ids, uint32_t &offset) const {
        for (const auto &id : ids) {
            if (getBlockHeight(id, offset)) {
                return true;
            }
        }

        return false;
    }

    std::vector<Crypto::Hash> BlockIndex::buildSparseChain(const Crypto::Hash &startBlockId) const {
        assert(m_index.count(startBlockId) > 0);

        uint32_t startBlockHeight = 0;
        size_t sparseChainEnd;
        getBlockHeight(startBlockId, startBlockHeight);

        std::vector<Crypto::Hash> result;
        sparseChainEnd = static_cast<size_t>(startBlockHeight + 1);
        for (size_t i = 1; i <= sparseChainEnd; i *= 2) {
            result.emplace_back(m_container[sparseChainEnd - i]);
        }

        if (result.back() != m_container[0]) {
            result.emplace_back(m_container[0]);
        }

        return result;
    }

    Crypto::Hash BlockIndex::getTailId() const {
        assert(!m_container.empty());
        return m_container.back();
    }

    void BlockIndex::serialize(ISerializer &s) {
        if (s.type() == ISerializer::INPUT) {
            readSequence<Crypto::Hash>(std::back_inserter(m_container), "index", s);
        } else {
            writeSequence<Crypto::Hash>(m_container.begin(), m_container.end(), "index", s);
        }
    }
}
