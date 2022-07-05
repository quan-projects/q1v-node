/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "CryptoNoteTools.h"
#include "CryptoNoteFormatUtils.h"

namespace Q1v {
template<>
bool toBinaryArray(const BinaryArray& object, BinaryArray& binaryArray) {
  try {
    Common::VectorOutputStream stream(binaryArray);
    BinaryOutputStreamSerializer serializer(stream);
    std::string oldBlob = Common::asString(object);
    serializer(oldBlob, "");
  } catch (std::exception&) {
    return false;
  }

  return true;
}

void getBinaryArrayHash(const BinaryArray& binaryArray, Crypto::Hash& hash) {
  q1v_fast_hash(binaryArray.data(), binaryArray.size(), hash);
}

Crypto::Hash getBinaryArrayHash(const BinaryArray& binaryArray) {
  Crypto::Hash hash;
  getBinaryArrayHash(binaryArray, hash);
  return hash;
}

uint64_t getInputAmount(const Transaction& transaction) {
  uint64_t amount = 0;
  for (auto& input : transaction.inputs) {
    if (input.type() == typeid(KeyInput)) {
      amount += boost::get<KeyInput>(input).amount;
    } else if (input.type() == typeid(MultisignatureInput)) {
      amount += boost::get<MultisignatureInput>(input).amount;
    }
  }

  return amount;
}

std::vector<uint64_t> getInputsAmounts(const Transaction& transaction) {
  std::vector<uint64_t> inputsAmounts;
  inputsAmounts.reserve(transaction.inputs.size());

  for (auto& input: transaction.inputs) {
    if (input.type() == typeid(KeyInput)) {
      inputsAmounts.push_back(boost::get<KeyInput>(input).amount);
    } else if (input.type() == typeid(MultisignatureInput)) {
      inputsAmounts.push_back(boost::get<MultisignatureInput>(input).amount);
    }
  }

  return inputsAmounts;
}

uint64_t getOutputAmount(const Transaction& transaction) {
  uint64_t amount = 0;
  for (auto& output : transaction.outputs) {
    amount += output.amount;
  }

  return amount;
}

void decomposeAmount(uint64_t amount, uint64_t dustThreshold, std::vector<uint64_t>& decomposedAmounts) {
  decompose_amount_into_digits(amount, dustThreshold,
    [&](uint64_t amount) {
    decomposedAmounts.push_back(amount);
  },
    [&](uint64_t dust) {
    decomposedAmounts.push_back(dust);
  }
  );
}

}
