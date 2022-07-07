/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <stddef.h>

#include <CryptoTypes.h>
#include "generic-ops.h"

namespace Crypto {

    extern "C" {

#include "hash-ops.h"

    }

    /*
      Cryptonight hash functions
    */

    inline void q1v_fast_hash(const void *data, size_t length, Hash &hash) {
        q1v_fast_hash(data, length, reinterpret_cast<char *>(&hash));
    }

    inline Hash q1v_fast_hash(const void *data, size_t length) {
        Hash h;
        q1v_fast_hash(data, length, reinterpret_cast<char *>(&h));
        return h;
    }

    class q1v_context {
    public:

        q1v_context();

        ~q1v_context();

#if !defined(_MSC_VER) || _MSC_VER >= 1800

        q1v_context(const q1v_context &) = delete;

        void operator=(const q1v_context &) = delete;

#endif

    private:

        void *data;

        friend inline void q1v_slow_hash(q1v_context &, const void *, size_t, Hash &);
    };

    inline void tree_hash(const Hash *hashes, size_t count, Hash &root_hash) {
        tree_hash(reinterpret_cast<const char (*)[HASH_SIZE]>(hashes), count, reinterpret_cast<char *>(&root_hash));
    }

    inline void tree_branch(const Hash *hashes, size_t count, Hash *branch) {
        tree_branch(reinterpret_cast<const char (*)[HASH_SIZE]>(hashes), count,
                    reinterpret_cast<char (*)[HASH_SIZE]>(branch));
    }

    inline void
    tree_hash_from_branch(const Hash *branch, size_t depth, const Hash &leaf, const void *path, Hash &root_hash) {
        tree_hash_from_branch(reinterpret_cast<const char (*)[HASH_SIZE]>(branch), depth,
                              reinterpret_cast<const char *>(&leaf), path, reinterpret_cast<char *>(&root_hash));
    }

}

CRYPTO_MAKE_HASHABLE(Hash)
