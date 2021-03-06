/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <system/Dispatcher.h>
#include <system/Event.h>
#include <system/InterruptedException.h>

namespace System {

    template<typename ResultType = void>
    class Context {
    public:
        Context(Dispatcher &dispatcher, std::function<ResultType()> &&target) : dispatcher(dispatcher),
                                                                                target(std::move(target)),
                                                                                ready(dispatcher), bindingContext(
                        dispatcher.getReusableContext()) {
            bindingContext.interrupted = false;
            bindingContext.groupNext = nullptr;
            bindingContext.groupPrev = nullptr;
            bindingContext.group = nullptr;
            bindingContext.procedure = [this] {
                try {
                    new(resultStorage) ResultType(this->target());
                } catch (...) {
                    exceptionPointer = std::current_exception();
                }

                ready.set();
            };

            dispatcher.pushContext(&bindingContext);
        }

        Context(const Context &) = delete;

        Context &operator=(const Context &) = delete;

        ~Context() {
            interrupt();
            wait();
            dispatcher.pushReusableContext(bindingContext);
        }

        ResultType &get() {
            wait();
            if (exceptionPointer != nullptr) {
                std::rethrow_exception(exceptionPointer);
            }

            return *reinterpret_cast<ResultType *>(resultStorage);
        }

        void interrupt() {
            dispatcher.interrupt(&bindingContext);
        }

        void wait() {
            for (;;) {
                try {
                    ready.wait();
                    break;
                } catch (InterruptedException &) {
                    interrupt();
                }
            }
        }

    private:
        uint8_t resultStorage[sizeof(ResultType)];
        Dispatcher &dispatcher;
        std::function<ResultType()> target;
        Event ready;
        NativeContext &bindingContext;
        std::exception_ptr exceptionPointer;
    };

    template<>
    class Context<void> {
    public:
        Context(Dispatcher &dispatcher, std::function<void()> &&target) : dispatcher(dispatcher),
                                                                          target(std::move(target)), ready(dispatcher),
                                                                          bindingContext(
                                                                                  dispatcher.getReusableContext()) {
            bindingContext.interrupted = false;
            bindingContext.groupNext = nullptr;
            bindingContext.groupPrev = nullptr;
            bindingContext.group = nullptr;
            bindingContext.procedure = [this] {
                try {
                    this->target();
                } catch (...) {
                    exceptionPointer = std::current_exception();
                }

                ready.set();
            };

            dispatcher.pushContext(&bindingContext);
        }

        Context(const Context &) = delete;

        Context &operator=(const Context &) = delete;

        ~Context() {
            interrupt();
            wait();
            dispatcher.pushReusableContext(bindingContext);
        }

        void get() {
            wait();
            if (exceptionPointer != nullptr) {
                std::rethrow_exception(exceptionPointer);
            }
        }

        void interrupt() {
            dispatcher.interrupt(&bindingContext);
        }

        void wait() {
            for (;;) {
                try {
                    ready.wait();
                    break;
                } catch (InterruptedException &) {
                    interrupt();
                }
            }
        }

    private:
        Dispatcher &dispatcher;
        std::function<void()> target;
        Event ready;
        NativeContext &bindingContext;
        std::exception_ptr exceptionPointer;
    };

}
