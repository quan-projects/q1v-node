/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include <CryptoNote.h>
#include "BinaryInputStreamSerializer.h"
#include "BinaryOutputStreamSerializer.h"
#include "common/MemoryInputStream.h"
#include "common/StdInputStream.h"
#include "common/StdOutputStream.h"
#include "common/VectorOutputStream.h"

#include <fstream>

namespace Q1v {

template <typename T>
BinaryArray storeToBinary(const T& obj) {
  BinaryArray result;
  Common::VectorOutputStream stream(result);
  BinaryOutputStreamSerializer ba(stream);
  serialize(const_cast<T&>(obj), ba);
  return result;
}

template <typename T>
void loadFromBinary(T& obj, const BinaryArray& blob) {
  Common::MemoryInputStream stream(blob.data(), blob.size());
  BinaryInputStreamSerializer ba(stream);
  serialize(obj, ba);
}

template <typename T>
bool storeToBinaryFile(const T& obj, const std::string& filename) {
  try {
    std::ofstream dataFile;
    dataFile.open(filename, std::ios_base::binary | std::ios_base::out | std::ios::trunc);
    if (dataFile.fail()) {
      return false;
    }

    Common::StdOutputStream stream(dataFile);
    BinaryOutputStreamSerializer out(stream);
    Q1v::serialize(const_cast<T&>(obj), out);
      
    if (dataFile.fail()) {
      return false;
    }

    dataFile.flush();
  } catch (std::exception&) {
    return false;
  }

  return true;
}

template<class T>
bool loadFromBinaryFile(T& obj, const std::string& filename) {
  try {
    std::ifstream dataFile;
    dataFile.open(filename, std::ios_base::binary | std::ios_base::in);
    if (dataFile.fail()) {
      return false;
    }

    Common::StdInputStream stream(dataFile);
    BinaryInputStreamSerializer in(stream);
    serialize(obj, in);
    return !dataFile.fail();
  } catch (std::exception&) {
    return false;
  }
}

}
