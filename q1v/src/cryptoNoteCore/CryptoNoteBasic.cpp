/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "CryptoNoteBasic.h"
#include "crypto/crypto.h"

namespace Q1v {

    KeyPair generateKeyPair() {
        KeyPair k;
        Crypto::generate_keys(k.publicKey, k.secretKey);
        return k;
    }

}
