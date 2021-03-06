/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <queue>

#include "IntrusiveLinkedList.h"

#include "system/Event.h"
#include "system/InterruptedException.h"

namespace Q1v {

    template<class MessageType>
    class MessageQueue {
    public:
        MessageQueue(System::Dispatcher &dispatcher);

        const MessageType &front();

        void pop();

        void push(const MessageType &message);

        void stop();

        typename IntrusiveLinkedList<MessageQueue<MessageType>>::hook &getHook();

    private:
        void wait();

        std::queue<MessageType> messageQueue;
        System::Event event;
        bool stopped;

        typename IntrusiveLinkedList<MessageQueue<MessageType>>::hook hook;
    };

    template<class MessageQueueContainer, class MessageType>
    class MesageQueueGuard {
    public:
        MesageQueueGuard(MessageQueueContainer &container, MessageQueue<MessageType> &messageQueue) : container(
                container), messageQueue(messageQueue) {
            container.addMessageQueue(messageQueue);
        }

        MesageQueueGuard(const MesageQueueGuard &other) = delete;

        MesageQueueGuard &operator=(const MesageQueueGuard &other) = delete;

        ~MesageQueueGuard() {
            container.removeMessageQueue(messageQueue);
        }

    private:
        MessageQueueContainer &container;
        MessageQueue<MessageType> &messageQueue;
    };

    template<class MessageType>
    MessageQueue<MessageType>::MessageQueue(System::Dispatcher &dispatcher) : event(dispatcher), stopped(false) {}

    template<class MessageType>
    void MessageQueue<MessageType>::wait() {
        if (messageQueue.empty()) {
            if (stopped) {
                throw System::InterruptedException();
            }

            event.clear();
            while (!event.get()) {
                event.wait();
            }
        }
    }

    template<class MessageType>
    const MessageType &MessageQueue<MessageType>::front() {
        wait();
        return messageQueue.front();
    }

    template<class MessageType>
    void MessageQueue<MessageType>::pop() {
        wait();
        messageQueue.pop();
    }

    template<class MessageType>
    void MessageQueue<MessageType>::push(const MessageType &message) {
        messageQueue.push(message);
        event.set();
    }

    template<class MessageType>
    void MessageQueue<MessageType>::stop() {
        stopped = true;
        event.set();
    }

    template<class MessageType>
    typename IntrusiveLinkedList<MessageQueue<MessageType>>::hook &MessageQueue<MessageType>::getHook() {
        return hook;
    }

}
