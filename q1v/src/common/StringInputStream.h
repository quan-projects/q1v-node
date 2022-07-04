/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <string>
#include "IInputStream.h"

namespace Common {

class StringInputStream : public IInputStream {
public:
  StringInputStream(const std::string& in);
  size_t readSome(void* data, size_t size) override;

private:
  const std::string& in;
  size_t offset;
};

}
