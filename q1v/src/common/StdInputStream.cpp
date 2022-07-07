/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "StdInputStream.h"

namespace Common {

    StdInputStream::StdInputStream(std::istream &in) : in(in) {
    }

    size_t StdInputStream::readSome(void *data, size_t size) {
        in.read(static_cast<char *>(data), size);
        return in.gcount();
    }

}
