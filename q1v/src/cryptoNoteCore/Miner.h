/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include <atomic>
#include <list>
#include <mutex>
#include <thread>

#include "cryptoNoteCore/CryptoNoteBasic.h"
#include "cryptoNoteCore/Currency.h"
#include "cryptoNoteCore/Difficulty.h"
#include "cryptoNoteCore/IMinerHandler.h"
#include "cryptoNoteCore/MinerConfig.h"
#include "cryptoNoteCore/OnceInInterval.h"

#include <logging/LoggerRef.h>

#include "serialization/ISerializer.h"

namespace Q1v {
    class miner {
    public:
        miner(const Currency &currency, IMinerHandler &handler, Logging::ILogger &log);

        ~miner();

        bool init(const MinerConfig &config);

        bool set_block_template(const Block &bl, const difficulty_type &diffic);

        bool on_block_chain_update();

        bool start(const AccountPublicAddress &adr, size_t threads_count);

        uint64_t get_speed();

        void send_stop_signal();

        bool stop();

        bool is_mining();

        bool on_idle();

        void on_synchronized();

        //synchronous analog (for fast calls)
        static bool find_nonce_for_given_block(Block &bl, const difficulty_type &diffic);

        void pause();

        void resume();

        void do_print_hashrate(bool do_hr);

    private:
        bool worker_thread(uint32_t th_local_index);

        bool request_block_template();

        void merge_hr();

        struct miner_config {
            uint64_t current_extra_message_index;

            void serialize(ISerializer &s) {
                KV_MEMBER(current_extra_message_index)
            }
        };

        const Currency &m_currency;
        Logging::LoggerRef logger;

        std::atomic<bool> m_stop;
        std::mutex m_template_lock;
        Block m_template;
        std::atomic<uint32_t> m_template_no;
        std::atomic<uint32_t> m_starter_nonce;
        difficulty_type m_diffic;

        std::atomic<uint32_t> m_threads_total;
        std::atomic<int32_t> m_pausers_count;
        std::mutex m_miners_count_lock;

        std::list<std::thread> m_threads;
        std::mutex m_threads_lock;
        IMinerHandler &m_handler;
        AccountPublicAddress m_mine_address;
        OnceInInterval m_update_block_template_interval;
        OnceInInterval m_update_merge_hr_interval;

        std::vector<BinaryArray> m_extra_messages;
        miner_config m_config;
        std::string m_config_folder_path;
        std::atomic<uint64_t> m_last_hr_merge_time;
        std::atomic<uint64_t> m_hashes;
        std::atomic<uint64_t> m_current_hash_rate;
        std::mutex m_last_hash_rates_lock;
        std::list<uint64_t> m_last_hash_rates;
        bool m_do_print_hashrate;
        bool m_do_mining;
    };
}
