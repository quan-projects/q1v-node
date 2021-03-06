/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "VectorOutputStream.h"

namespace Common {

    VectorOutputStream::VectorOutputStream(std::vector<uint8_t> &out) : out(out) {
    }

    size_t VectorOutputStream::writeSome(const void *data, size_t size) {
        out.insert(out.end(), static_cast<const uint8_t *>(data), static_cast<const uint8_t *>(data) + size);
        return size;
    }

}
