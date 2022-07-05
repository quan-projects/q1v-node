/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "serialization/JsonInputStreamSerializer.h"

#include <ctype.h>
#include <exception>

namespace Q1v {

namespace {

Common::JsonValue getJsonValueFromStreamHelper(std::istream& stream) {
  Common::JsonValue value;
  stream >> value;
  return value;
}

}

JsonInputStreamSerializer::JsonInputStreamSerializer(std::istream& stream) : JsonInputValueSerializer(getJsonValueFromStreamHelper(stream)) {
}

JsonInputStreamSerializer::~JsonInputStreamSerializer() {
}

} //namespace Q1v
