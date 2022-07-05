/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <istream>
#include "IInputStream.h"

namespace Common {

    class StdInputStream : public IInputStream {
    public:
        StdInputStream(std::istream &in);

        StdInputStream &operator=(const StdInputStream &) = delete;

        size_t readSome(void *data, size_t size) override;

    private:
        std::istream &in;
    };

}
