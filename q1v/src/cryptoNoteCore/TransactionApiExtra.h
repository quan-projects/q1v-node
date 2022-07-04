/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
 *
*/

#pragma once

#include "CryptoNoteFormatUtils.h"
#include "TransactionExtra.h"

namespace Q1v {

  class TransactionExtra {
  public:
    TransactionExtra() {}
    TransactionExtra(const std::vector<uint8_t>& extra) {
      parse(extra);        
    }

    bool parse(const std::vector<uint8_t>& extra) {
      fields.clear();
      return Q1v::parseTransactionExtra(extra, fields);
    }

    template <typename T>
    bool get(T& value) const {
      auto it = find(typeid(T));
      if (it == fields.end()) {
        return false;
      }
      value = boost::get<T>(*it);
      return true;
    }

    template <typename T>
    void set(const T& value) {
      auto it = find(typeid(T));
      if (it != fields.end()) {
        *it = value;
      } else {
        fields.push_back(value);
      }
    }

    template <typename T>
    void append(const T& value) {
      fields.push_back(value);
    }

    bool getPublicKey(Crypto::PublicKey& pk) const {
      Q1v::TransactionExtraPublicKey extraPk;
      if (!get(extraPk)) {
        return false;
      }
      pk = extraPk.publicKey;
      return true;
    }

    std::vector<uint8_t> serialize() const {
      std::vector<uint8_t> extra;
      writeTransactionExtra(extra, fields);
      return extra;
    }

  private:

    std::vector<Q1v::TransactionExtraField>::const_iterator find(const std::type_info& t) const {
      return std::find_if(fields.begin(), fields.end(), [&t](const Q1v::TransactionExtraField& f) { return t == f.type(); });
    }

    std::vector<Q1v::TransactionExtraField>::iterator find(const std::type_info& t) {
      return std::find_if(fields.begin(), fields.end(), [&t](const Q1v::TransactionExtraField& f) { return t == f.type(); });
    }

    std::vector<Q1v::TransactionExtraField> fields;
  };

}
