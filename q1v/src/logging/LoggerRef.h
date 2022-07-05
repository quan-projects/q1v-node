/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "ILogger.h"
#include "LoggerMessage.h"

namespace Logging {

    class LoggerRef {
    public:
        LoggerRef(ILogger &logger, const std::string &category);

        LoggerMessage operator()(Level level = INFO, const std::string &color = DEFAULT) const;

        ILogger &getLogger() const;

    private:
        ILogger *logger;
        std::string category;
    };

}
