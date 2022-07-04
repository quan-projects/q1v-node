/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include "serialization/ISerializer.h"

namespace Q1v
{
  struct core_stat_info
  {
    uint64_t tx_pool_size;
    uint64_t blockchain_height;
    uint64_t mining_speed;
    uint64_t alternative_blocks;
    std::string top_block_id_str;
    
    void serialize(ISerializer& s) {
      KV_MEMBER(tx_pool_size)
      KV_MEMBER(blockchain_height)
      KV_MEMBER(mining_speed)
      KV_MEMBER(alternative_blocks)
      KV_MEMBER(top_block_id_str)
    }
  };
}
