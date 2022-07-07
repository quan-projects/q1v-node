/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <vector>

#include <CryptoNote.h>

namespace Q1v {

    class NewBlockMessage {
    public:
        NewBlockMessage(const Crypto::Hash &hash);

        NewBlockMessage() = default;

        void get(Crypto::Hash &hash) const;

    private:
        Crypto::Hash blockHash;
    };

    class NewAlternativeBlockMessage {
    public:
        NewAlternativeBlockMessage(const Crypto::Hash &hash);

        NewAlternativeBlockMessage() = default;

        void get(Crypto::Hash &hash) const;

    private:
        Crypto::Hash blockHash;
    };

    class ChainSwitchMessage {
    public:
        ChainSwitchMessage(std::vector<Crypto::Hash> &&hashes);

        ChainSwitchMessage(const ChainSwitchMessage &other);

        void get(std::vector<Crypto::Hash> &hashes) const;

    private:
        std::vector<Crypto::Hash> blocksFromCommonRoot;
    };

    class BlockchainMessage {
    public:
        enum class MessageType {
            NEW_BLOCK_MESSAGE, NEW_ALTERNATIVE_BLOCK_MESSAGE, CHAIN_SWITCH_MESSAGE
        };

        BlockchainMessage(NewBlockMessage &&message);

        BlockchainMessage(NewAlternativeBlockMessage &&message);

        BlockchainMessage(ChainSwitchMessage &&message);

        BlockchainMessage(const BlockchainMessage &other);

        ~BlockchainMessage();

        MessageType getType() const;

        bool getNewBlockHash(Crypto::Hash &hash) const;

        bool getNewAlternativeBlockHash(Crypto::Hash &hash) const;

        bool getChainSwitch(std::vector<Crypto::Hash> &hashes) const;

    private:
        const MessageType type;

        union {
            NewBlockMessage newBlockMessage;
            NewAlternativeBlockMessage newAlternativeBlockMessage;
            ChainSwitchMessage *chainSwitchMessage;
        };
    };

}
