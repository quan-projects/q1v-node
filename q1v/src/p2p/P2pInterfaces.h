/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <cstdint>
#include <memory>

#include <CryptoNote.h>

namespace Q1v {

struct P2pMessage {
  uint32_t type;
  BinaryArray data;
};

class IP2pConnection {
public:
  virtual ~IP2pConnection();
  virtual void read(P2pMessage &message) = 0;
  virtual void write(const P2pMessage &message) = 0;
  virtual void ban() = 0;
  virtual void stop() = 0;
};

class IP2pNode {
public:
  virtual std::unique_ptr<IP2pConnection> receiveConnection() = 0;
  virtual void stop() = 0;
};

}
