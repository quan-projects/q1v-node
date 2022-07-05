/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <cstdint>
#include <string>

namespace System {

class Ipv4Address {
public:
  explicit Ipv4Address(uint32_t value);
  explicit Ipv4Address(const std::string& dottedDecimal);
  bool operator!=(const Ipv4Address& other) const;
  bool operator==(const Ipv4Address& other) const;
  uint32_t getValue() const;
  bool isLoopback() const;
  bool isPrivate() const;
  std::string toDottedDecimal() const;

private:
  uint32_t value;
};

}
