/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "CryptoNoteBasic.h"
#include "crypto/chacha8.h"
#include "serialization/ISerializer.h"
#include "crypto/crypto.h"

namespace Crypto {

bool serialize(PublicKey& pubKey, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(SecretKey& secKey, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(Hash& h, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(chacha8_iv& chacha, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(KeyImage& keyImage, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(Signature& sig, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(EllipticCurveScalar& ecScalar, Common::StringView name, Q1v::ISerializer& serializer);
bool serialize(EllipticCurvePoint& ecPoint, Common::StringView name, Q1v::ISerializer& serializer);

}

namespace Q1v {

struct AccountKeys;
struct TransactionExtraMergeMiningTag;

void serialize(TransactionPrefix& txP, ISerializer& serializer);
void serialize(Transaction& tx, ISerializer& serializer);
void serialize(TransactionInput& in, ISerializer& serializer);
void serialize(TransactionOutput& in, ISerializer& serializer);

void serialize(BaseInput& gen, ISerializer& serializer);
void serialize(KeyInput& key, ISerializer& serializer);
void serialize(MultisignatureInput& multisignature, ISerializer& serializer);

void serialize(TransactionOutput& output, ISerializer& serializer);
void serialize(TransactionOutputTarget& output, ISerializer& serializer);
void serialize(KeyOutput& key, ISerializer& serializer);
void serialize(MultisignatureOutput& multisignature, ISerializer& serializer);

void serialize(BlockHeader& header, ISerializer& serializer);
void serialize(Block& block, ISerializer& serializer);
void serialize(ParentBlockSerializer& pbs, ISerializer& serializer);
void serialize(TransactionExtraMergeMiningTag& tag, ISerializer& serializer);

void serialize(AccountPublicAddress& address, ISerializer& serializer);
void serialize(AccountKeys& keys, ISerializer& s);

void serialize(KeyPair& keyPair, ISerializer& serializer);

}
