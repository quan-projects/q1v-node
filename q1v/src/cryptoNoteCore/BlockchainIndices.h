/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <boost/functional/hash.hpp>
#include <map>
#include <string>
#include <unordered_map>

#include "crypto/hash.h"
#include "CryptoNoteBasic.h"

namespace Q1v {

    class ISerializer;

    inline size_t paymentIdHash(const Crypto::Hash &paymentId) {
        return boost::hash_range(std::begin(paymentId.data), std::end(paymentId.data));
    }

    class PaymentIdIndex {
    public:
        PaymentIdIndex(bool enabled);

        bool add(const Transaction &transaction);

        bool remove(const Transaction &transaction);

        bool find(const Crypto::Hash &paymentId, std::vector<Crypto::Hash> &transactionHashes);

        void clear();

        void serialize(ISerializer &s);

        template<class Archive>
        void serialize(Archive &archive, unsigned int version) {
            archive & index;
        }

    private:
        std::unordered_multimap<Crypto::Hash, Crypto::Hash, std::function<decltype(paymentIdHash)>> index;
        bool enabled = false;
    };

    class TimestampBlocksIndex {
    public:
        TimestampBlocksIndex(bool enabled);

        bool add(uint64_t timestamp, const Crypto::Hash &hash);

        bool remove(uint64_t timestamp, const Crypto::Hash &hash);

        bool find(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t hashesNumberLimit,
                  std::vector<Crypto::Hash> &hashes, uint32_t &hashesNumberWithinTimestamps);

        void clear();

        void serialize(ISerializer &s);

        template<class Archive>
        void serialize(Archive &archive, unsigned int version) {
            archive & index;
        }

    private:
        std::multimap<uint64_t, Crypto::Hash> index;
        bool enabled = false;
    };

    class TimestampTransactionsIndex {
    public:
        TimestampTransactionsIndex(bool enabled);

        bool add(uint64_t timestamp, const Crypto::Hash &hash);

        bool remove(uint64_t timestamp, const Crypto::Hash &hash);

        bool find(uint64_t timestampBegin, uint64_t timestampEnd, uint64_t hashesNumberLimit,
                  std::vector<Crypto::Hash> &hashes, uint64_t &hashesNumberWithinTimestamps);

        void clear();

        void serialize(ISerializer &s);

        template<class Archive>
        void serialize(Archive &archive, unsigned int version) {
            archive & index;
        }

    private:
        std::multimap<uint64_t, Crypto::Hash> index;
        bool enabled = false;
    };

    class GeneratedTransactionsIndex {
    public:
        GeneratedTransactionsIndex(bool enabled);

        bool add(const Block &block);

        bool remove(const Block &block);

        bool find(uint32_t height, uint64_t &generatedTransactions);

        void clear();

        void serialize(ISerializer &s);

        template<class Archive>
        void serialize(Archive &archive, unsigned int version) {
            archive & index;
            archive & lastGeneratedTxNumber;
        }

    private:
        std::unordered_map<uint32_t, uint64_t> index;
        uint64_t lastGeneratedTxNumber;
        bool enabled = false;
    };

    class OrphanBlocksIndex {
    public:
        OrphanBlocksIndex(bool enabled);

        bool add(const Block &block);

        bool remove(const Block &block);

        bool find(uint32_t height, std::vector<Crypto::Hash> &blockHashes);

        void clear();

    private:
        std::unordered_multimap<uint32_t, Crypto::Hash> index;
        bool enabled = false;
    };

}
