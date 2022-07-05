/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "cryptoNoteCore/CryptoNoteBasic.h"
#include "ITransaction.h"

namespace Q1v {

    bool checkInputsKeyimagesDiff(const Q1v::TransactionPrefix &tx);

// TransactionInput helper functions
    size_t getRequiredSignaturesCount(const TransactionInput &in);

    uint64_t getTransactionInputAmount(const TransactionInput &in);

    TransactionTypes::InputType getTransactionInputType(const TransactionInput &in);

    const TransactionInput &getInputChecked(const Q1v::TransactionPrefix &transaction, size_t index);

    const TransactionInput &
    getInputChecked(const Q1v::TransactionPrefix &transaction, size_t index, TransactionTypes::InputType type);

    bool isOutToKey(const Crypto::PublicKey &spendPublicKey, const Crypto::PublicKey &outKey,
                    const Crypto::KeyDerivation &derivation, size_t keyIndex);

// TransactionOutput helper functions
    TransactionTypes::OutputType getTransactionOutputType(const TransactionOutputTarget &out);

    const TransactionOutput &getOutputChecked(const Q1v::TransactionPrefix &transaction, size_t index);

    const TransactionOutput &
    getOutputChecked(const Q1v::TransactionPrefix &transaction, size_t index, TransactionTypes::OutputType type);

    bool findOutputsToAccount(const Q1v::TransactionPrefix &transaction, const AccountPublicAddress &addr,
                              const Crypto::SecretKey &viewSecretKey, std::vector<uint32_t> &out, uint64_t &amount);

} //namespace Q1v
