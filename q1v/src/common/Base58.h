/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <cstdint>
#include <string>

namespace Tools {
    namespace Base58 {
        std::string encode(const std::string &data);

        bool decode(const std::string &enc, std::string &data);

        std::string encode_addr(uint64_t tag, const std::string &data);

        bool decode_addr(std::string addr, uint64_t &tag, std::string &data);
    }
}
