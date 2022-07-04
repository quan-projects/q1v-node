/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <cstddef>

namespace Common {

class IInputStream {
public:
  virtual ~IInputStream() { }
  virtual size_t readSome(void* data, size_t size) = 0;
};

}
