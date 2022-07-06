/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#include "SignalHandler.h"

#include <mutex>
#include <iostream>
#include <signal.h>
#include <cstring>

namespace {

    std::function<void(void)> m_handler;

    void handleSignal() {
        static std::mutex m_mutex;
        std::unique_lock<std::mutex> lock(m_mutex, std::try_to_lock);
        if (!lock.owns_lock()) {
            return;
        }
        m_handler();
    }

    void posixHandler(int /*type*/) {
        handleSignal();
    }
}

namespace Tools {
    bool SignalHandler::install(std::function<void(void)> t) {
        struct sigaction newMask;
        std::memset(&newMask, 0, sizeof(struct sigaction));
        newMask.sa_handler = posixHandler;
        if (sigaction(SIGINT, &newMask, nullptr) != 0) {
            return false;
        }

        if (sigaction(SIGTERM, &newMask, nullptr) != 0) {
            return false;
        }

        std::memset(&newMask, 0, sizeof(struct sigaction));
        newMask.sa_handler = SIG_IGN;
        if (sigaction(SIGPIPE, &newMask, nullptr) != 0) {
            return false;
        }

        m_handler = t;
        return true;
    }
}
