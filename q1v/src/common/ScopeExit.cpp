/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "ScopeExit.h"

namespace Tools {

    ScopeExit::ScopeExit(std::function<void()> &&handler) : m_handler(std::move(handler)), m_cancelled(false) {
    }

    ScopeExit::~ScopeExit() {
        if (!m_cancelled) {
            m_handler();
        }
    }

    void ScopeExit::cancel() {
        m_cancelled = true;
    }

}
