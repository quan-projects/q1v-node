/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#include "StreamLogger.h"
#include <iostream>
#include <sstream>

namespace Logging {

StreamLogger::StreamLogger(Level level) : CommonLogger(level), stream(nullptr) {
}

StreamLogger::StreamLogger(std::ostream& stream, Level level) : CommonLogger(level), stream(&stream) {
}

void StreamLogger::attachToStream(std::ostream& stream) {
  this->stream = &stream;
}

void StreamLogger::doLogString(const std::string& message) {
  if (stream != nullptr && stream->good()) {
    std::lock_guard<std::mutex> lock(mutex);
    bool readingText = true;
    for (size_t charPos = 0; charPos < message.size(); ++charPos) {
      if (message[charPos] == ILogger::COLOR_DELIMETER) {
        readingText = !readingText;
      } else if (readingText) {
        *stream << message[charPos];
      }
    }

    *stream << std::flush;
  }
}

}
