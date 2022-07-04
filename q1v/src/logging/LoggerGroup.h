/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <vector>
#include "CommonLogger.h"

namespace Logging {

class LoggerGroup : public CommonLogger {
public:
  LoggerGroup(Level level = DEBUGGING);

  void addLogger(ILogger& logger);
  void removeLogger(ILogger& logger);
  virtual void operator()(const std::string& category, Level level, boost::posix_time::ptime time, const std::string& body) override;

protected:
  std::vector<ILogger*> loggers;
};

}
