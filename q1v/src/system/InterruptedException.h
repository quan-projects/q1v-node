/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <exception>

namespace System {

    class InterruptedException : public std::exception {
    public:
        virtual const char *what() const throw() override {
            return "interrupted";
        }
    };

}
