/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <boost/utility/value_init.hpp>
#include <CryptoNote.h>

namespace Q1v {
    const Crypto::Hash NULL_HASH = boost::value_initialized<Crypto::Hash>();
    const Crypto::PublicKey NULL_PUBLIC_KEY = boost::value_initialized<Crypto::PublicKey>();
    const Crypto::SecretKey NULL_SECRET_KEY = boost::value_initialized<Crypto::SecretKey>();

    KeyPair generateKeyPair();

    struct ParentBlockSerializer {
        ParentBlockSerializer(ParentBlock &parentBlock, uint64_t &timestamp, uint32_t &nonce, bool hashingSerialization,
                              bool headerOnly) : m_parentBlock(parentBlock), m_timestamp(timestamp), m_nonce(nonce),
                                                 m_hashingSerialization(hashingSerialization),
                                                 m_headerOnly(headerOnly) {
        }

        ParentBlock &m_parentBlock;
        uint64_t &m_timestamp;
        uint32_t &m_nonce;
        bool m_hashingSerialization;
        bool m_headerOnly;
    };

    inline ParentBlockSerializer makeParentBlockSerializer(const Block &b, bool hashingSerialization, bool headerOnly) {
        Block &blockRef = const_cast<Block &>(b);
        return ParentBlockSerializer(blockRef.parentBlock, blockRef.timestamp, blockRef.nonce, hashingSerialization,
                                     headerOnly);
    }

}
