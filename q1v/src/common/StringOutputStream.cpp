/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "StringOutputStream.h"

namespace Common {

    StringOutputStream::StringOutputStream(std::string &out) : out(out) {
    }

    size_t StringOutputStream::writeSome(const void *data, size_t size) {
        out.append(static_cast<const char *>(data), size);
        return size;
    }

}
