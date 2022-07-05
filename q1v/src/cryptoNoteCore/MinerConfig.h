/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <cstdint>
#include <string>

#include <boost/program_options.hpp>

namespace Q1v {

    class MinerConfig {
    public:
        MinerConfig();

        static void initOptions(boost::program_options::options_description &desc);

        void init(const boost::program_options::variables_map &options);

        std::string extraMessages;
        std::string startMining;
        uint32_t miningThreads;
    };

} //namespace Q1v
