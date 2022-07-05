/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <cstdint>
#include <functional>
#include <system_error>
#include <vector>

#include "crypto/crypto.h"
#include "cryptoNoteCore/CryptoNoteBasic.h"
#include "cryptoNoteProtocol/CryptoNoteProtocolDefinitions.h"
#include "rpc/CoreRpcServerCommandsDefinitions.h"

#include "BlockchainExplorerData.h"
#include "ITransaction.h"

namespace Q1v {

    class INodeObserver {
    public:
        virtual ~INodeObserver() {}

        virtual void peerCountUpdated(size_t count) {}

        virtual void localBlockchainUpdated(uint32_t height) {}

        virtual void lastKnownBlockHeightUpdated(uint32_t height) {}

        virtual void poolChanged() {}

        virtual void blockchainSynchronized(uint32_t topHeight) {}
    };

    struct OutEntry {
        uint32_t outGlobalIndex;
        Crypto::PublicKey outKey;
    };

    struct OutsForAmount {
        uint64_t amount;
        std::vector<OutEntry> outs;
    };

    struct TransactionShortInfo {
        Crypto::Hash txId;
        TransactionPrefix txPrefix;
    };

    struct BlockShortEntry {
        Crypto::Hash blockHash;
        bool hasBlock;
        Q1v::Block block;
        std::vector<TransactionShortInfo> txsShortInfo;
    };

    struct BlockHeaderInfo {
        uint32_t index;
        uint8_t majorVersion;
        uint8_t minorVersion;
        uint64_t timestamp;
        Crypto::Hash hash;
        Crypto::Hash prevHash;
        uint32_t nonce;
        bool isAlternative;
        uint32_t depth; // last block index = current block index + depth
        difficulty_type difficulty;
        uint64_t reward;
    };

    class INode {
    public:
        typedef std::function<void(std::error_code)> Callback;

        virtual ~INode() {}

        virtual bool addObserver(INodeObserver *observer) = 0;

        virtual bool removeObserver(INodeObserver *observer) = 0;

        virtual void init(const Callback &callback) = 0;

        virtual bool shutdown() = 0;

        virtual size_t getPeerCount() const = 0;

        virtual uint32_t getLastLocalBlockHeight() const = 0;

        virtual uint32_t getLastKnownBlockHeight() const = 0;

        virtual uint32_t getLocalBlockCount() const = 0;

        virtual uint32_t getKnownBlockCount() const = 0;

        virtual uint64_t getLastLocalBlockTimestamp() const = 0;

        virtual BlockHeaderInfo getLastLocalBlockHeaderInfo() const = 0;

        virtual void relayTransaction(const Transaction &transaction, const Callback &callback) = 0;

        virtual void getRandomOutsByAmounts(std::vector<uint64_t> &&amounts, uint64_t outsCount,
                                            std::vector<Q1v::COMMAND_RPC_GET_RANDOM_OUTPUTS_FOR_AMOUNTS::outs_for_amount> &result,
                                            const Callback &callback) = 0;

        virtual void
        getNewBlocks(std::vector<Crypto::Hash> &&knownBlockIds, std::vector<Q1v::block_complete_entry> &newBlocks,
                     uint32_t &startHeight, const Callback &callback) = 0;

        virtual void
        getTransactionOutsGlobalIndices(const Crypto::Hash &transactionHash, std::vector<uint32_t> &outsGlobalIndices,
                                        const Callback &callback) = 0;

        virtual void queryBlocks(std::vector<Crypto::Hash> &&knownBlockIds, uint64_t timestamp,
                                 std::vector<BlockShortEntry> &newBlocks, uint32_t &startHeight,
                                 const Callback &callback) = 0;

        virtual void getPoolSymmetricDifference(std::vector<Crypto::Hash> &&knownPoolTxIds, Crypto::Hash knownBlockId,
                                                bool &isBcActual,
                                                std::vector<std::unique_ptr<ITransactionReader>> &newTxs,
                                                std::vector<Crypto::Hash> &deletedTxIds, const Callback &callback) = 0;

        virtual void getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t gindex, MultisignatureOutput &out,
                                                          const Callback &callback) = 0;

        virtual void
        getBlocks(const std::vector<uint32_t> &blockHeights, std::vector<std::vector<BlockDetails>> &blocks,
                  const Callback &callback) = 0;

        virtual void getBlocks(const std::vector<Crypto::Hash> &blockHashes, std::vector<BlockDetails> &blocks,
                               const Callback &callback) = 0;

        virtual void getBlocks(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit,
                               std::vector<BlockDetails> &blocks, uint32_t &blocksNumberWithinTimestamps,
                               const Callback &callback) = 0;

        virtual void getTransactions(const std::vector<Crypto::Hash> &transactionHashes,
                                     std::vector<TransactionDetails> &transactions, const Callback &callback) = 0;

        virtual void
        getTransactionsByPaymentId(const Crypto::Hash &paymentId, std::vector<TransactionDetails> &transactions,
                                   const Callback &callback) = 0;

        virtual void
        getPoolTransactions(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit,
                            std::vector<TransactionDetails> &transactions, uint64_t &transactionsNumberWithinTimestamps,
                            const Callback &callback) = 0;

        virtual void isSynchronized(bool &syncStatus, const Callback &callback) = 0;
    };

}
