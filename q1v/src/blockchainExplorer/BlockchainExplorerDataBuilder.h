/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <vector>
#include <array>

#include "cryptoNoteProtocol/ICryptoNoteProtocolQuery.h"
#include "cryptoNoteCore/ICore.h"
#include "BlockchainExplorerData.h"

namespace Q1v {

    class BlockchainExplorerDataBuilder {
    public:
        BlockchainExplorerDataBuilder(Q1v::ICore &core, Q1v::ICryptoNoteProtocolQuery &protocol);

        BlockchainExplorerDataBuilder(const BlockchainExplorerDataBuilder &) = delete;

        BlockchainExplorerDataBuilder(BlockchainExplorerDataBuilder &&) = delete;

        BlockchainExplorerDataBuilder &operator=(const BlockchainExplorerDataBuilder &) = delete;

        BlockchainExplorerDataBuilder &operator=(BlockchainExplorerDataBuilder &&) = delete;

        bool fillBlockDetails(const Block &block, BlockDetails &blockDetails);

        bool fillTransactionDetails(const Transaction &tx, TransactionDetails &txRpcInfo, uint64_t timestamp = 0);

        static bool getPaymentId(const Transaction &transaction, Crypto::Hash &paymentId);

    private:
        bool getMixin(const Transaction &transaction, uint64_t &mixin);

        bool fillTxExtra(const std::vector<uint8_t> &rawExtra, TransactionExtraDetails &extraDetails);

        size_t median(std::vector<size_t> &v);

        Q1v::ICore &core;
        Q1v::ICryptoNoteProtocolQuery &protocol;
    };
}
