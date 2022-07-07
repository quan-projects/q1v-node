/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "cryptoNoteCore/CryptoNoteBasic.h"
#include "cryptoNoteCore/Difficulty.h"

namespace Q1v {
    struct IMinerHandler {
        virtual bool handle_block_found(Block &b) = 0;

        virtual bool
        get_block_template(Block &b, const AccountPublicAddress &adr, difficulty_type &diffic, uint32_t &height,
                           const BinaryArray &ex_nonce) = 0;

    protected:
        ~IMinerHandler() {};
    };
}
