/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <list>
#include <memory>
#include <mutex>
#include "../common/JsonValue.h"
#include "LoggerGroup.h"

namespace Logging {

    class LoggerManager : public LoggerGroup {
    public:
        LoggerManager();

        void configure(const Common::JsonValue &val);

        virtual void operator()(const std::string &category, Level level, boost::posix_time::ptime time,
                                const std::string &body) override;

    private:
        std::vector<std::unique_ptr<CommonLogger>> loggers;
        std::mutex reconfigureLock;
    };

}
