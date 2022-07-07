/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "common/ConsoleHandler.h"

#include <logging/LoggerRef.h>
#include <logging/LoggerManager.h>

namespace Q1v {
    class core;

    class NodeServer;
}

class DaemonCommandsHandler {
public:
    DaemonCommandsHandler(Q1v::core &core, Q1v::NodeServer &srv, Logging::LoggerManager &log);

    bool start_handling() {
        m_consoleHandler.start();
        return true;
    }

    void stop_handling() {
        m_consoleHandler.stop();
    }

private:

    Common::ConsoleHandler m_consoleHandler;
    Q1v::core &m_core;
    Q1v::NodeServer &m_srv;
    Logging::LoggerRef logger;
    Logging::LoggerManager &m_logManager;

    std::string get_commands_str();

    bool print_block_by_height(uint32_t height);

    bool print_block_by_hash(const std::string &arg);

    bool exit(const std::vector<std::string> &args);

    bool help(const std::vector<std::string> &args);

    bool print_pl(const std::vector<std::string> &args);

    bool show_hr(const std::vector<std::string> &args);

    bool hide_hr(const std::vector<std::string> &args);

    bool print_bc_outs(const std::vector<std::string> &args);

    bool print_cn(const std::vector<std::string> &args);

    bool print_bc(const std::vector<std::string> &args);

    bool print_bci(const std::vector<std::string> &args);

    bool set_log(const std::vector<std::string> &args);

    bool print_block(const std::vector<std::string> &args);

    bool print_tx(const std::vector<std::string> &args);

    bool print_pool(const std::vector<std::string> &args);

    bool print_pool_sh(const std::vector<std::string> &args);

    bool start_mining(const std::vector<std::string> &args);

    bool stop_mining(const std::vector<std::string> &args);
};
