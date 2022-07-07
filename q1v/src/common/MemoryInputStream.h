/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "IInputStream.h"

namespace Common {

    class MemoryInputStream : public IInputStream {
    public:
        MemoryInputStream(const void *buffer, size_t bufferSize);

        size_t getPosition() const;

        bool endOfStream() const;

        // IInputStream
        virtual size_t readSome(void *data, size_t size) override;

    private:
        const char *buffer;
        size_t bufferSize;
        size_t position;
    };
}
