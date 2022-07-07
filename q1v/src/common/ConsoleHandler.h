/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <atomic>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <vector>

#include "BlockingQueue.h"
#include "ConsoleTools.h"

namespace Common {

    class AsyncConsoleReader {

    public:

        AsyncConsoleReader();

        ~AsyncConsoleReader();

        void start();

        bool getline(std::string &line);

        void stop();

        bool stopped() const;

    private:

        void consoleThread();

        bool waitInput();

        std::atomic<bool> m_stop;
        std::thread m_thread;
        BlockingQueue<std::string> m_queue;
    };

    class ConsoleHandler {
    public:

        ~ConsoleHandler();

        typedef std::function<bool(const std::vector<std::string> &)> ConsoleCommandHandler;

        std::string getUsage() const;

        void
        setHandler(const std::string &command, const ConsoleCommandHandler &handler, const std::string &usage = "");

        void requestStop();

        bool runCommand(const std::vector<std::string> &cmdAndArgs);

        void start(bool startThread = true, const std::string &prompt = "",
                   Console::Color promptColor = Console::Color::Default);

        void stop();

        void wait();

    private:

        typedef std::map<std::string, std::pair<ConsoleCommandHandler, std::string>> CommandHandlersMap;

        virtual void handleCommand(const std::string &cmd);

        void handlerThread();

        std::thread m_thread;
        std::string m_prompt;
        Console::Color m_promptColor = Console::Color::Default;
        CommandHandlersMap m_handlers;
        AsyncConsoleReader m_consoleReader;
    };

}
