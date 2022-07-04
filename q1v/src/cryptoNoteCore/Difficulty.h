/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <cstdint>
#include <vector>

#include "crypto/hash.h"

namespace Q1v
{
    typedef std::uint64_t difficulty_type;

    bool check_hash(const Crypto::Hash &hash, difficulty_type difficulty);
}
