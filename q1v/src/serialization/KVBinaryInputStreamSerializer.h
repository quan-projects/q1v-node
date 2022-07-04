/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <common/IInputStream.h>
#include "ISerializer.h"
#include "JsonInputValueSerializer.h"

namespace Q1v {

class KVBinaryInputStreamSerializer : public JsonInputValueSerializer {
public:
  KVBinaryInputStreamSerializer(Common::IInputStream& strm);

  virtual bool binary(void* value, size_t size, Common::StringView name) override;
  virtual bool binary(std::string& value, Common::StringView name) override;
};

}
