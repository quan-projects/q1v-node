/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "CryptoNote.h"

namespace Q1v {
    class IBlock {
    public:
        virtual ~IBlock();

        virtual const Block &getBlock() const = 0;

        virtual size_t getTransactionCount() const = 0;

        virtual const Transaction &getTransaction(size_t index) const = 0;
    };
}
