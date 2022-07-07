/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <unordered_set>

#include <http/HttpRequest.h>
#include <http/HttpResponse.h>

#include <system/ContextGroup.h>
#include <system/Dispatcher.h>
#include <system/TcpListener.h>
#include <system/TcpConnection.h>
#include <system/Event.h>

#include <logging/LoggerRef.h>

namespace Q1v {

    class HttpServer {

    public:

        HttpServer(System::Dispatcher &dispatcher, Logging::ILogger &log);

        void start(const std::string &address, uint16_t port, const std::string &user = "",
                   const std::string &password = "");

        void stop();

        virtual void processRequest(const HttpRequest &request, HttpResponse &response) = 0;

    protected:

        System::Dispatcher &m_dispatcher;

    private:

        void acceptLoop();

        void connectionHandler(System::TcpConnection &&conn);

        bool authenticate(const HttpRequest &request) const;

        System::ContextGroup workingContextGroup;
        Logging::LoggerRef logger;
        System::TcpListener m_listener;
        std::unordered_set<System::TcpConnection *> m_connections;
        std::string m_credentials;
    };

}
