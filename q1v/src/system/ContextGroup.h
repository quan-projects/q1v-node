/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <system/Dispatcher.h>

namespace System {

    class ContextGroup {
    public:
        explicit ContextGroup(Dispatcher &dispatcher);

        ContextGroup(const ContextGroup &) = delete;

        ContextGroup(ContextGroup &&other);

        ~ContextGroup();

        ContextGroup &operator=(const ContextGroup &) = delete;

        ContextGroup &operator=(ContextGroup &&other);

        void interrupt();

        void spawn(std::function<void()> &&procedure);

        void wait();

    private:
        Dispatcher *dispatcher;
        NativeContextGroup contextGroup;
    };

}
