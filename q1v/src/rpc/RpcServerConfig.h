/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include <boost/program_options.hpp>

namespace Q1v {

class RpcServerConfig {
public:

  RpcServerConfig();

  static void initOptions(boost::program_options::options_description& desc);
  void init(const boost::program_options::variables_map& options);

  std::string getBindAddress() const;

  std::string bindIp;
  uint16_t bindPort;
};

}
