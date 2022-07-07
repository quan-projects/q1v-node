/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <fstream>
#include "StreamLogger.h"

namespace Logging {

    class FileLogger : public StreamLogger {
    public:
        FileLogger(Level level = DEBUGGING);

        void init(const std::string &filename);

    private:
        std::ofstream fileStream;
    };

}
