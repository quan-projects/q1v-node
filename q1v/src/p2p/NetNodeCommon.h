/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/bytecoin_copyright.txt"
*/

#pragma once

#include "CryptoNote.h"
#include "P2pProtocolTypes.h"

namespace Q1v {

    struct CryptoNoteConnectionContext;

    struct IP2pEndpoint {
        virtual void
        relay_notify_to_all(int command, const BinaryArray &data_buff, const net_connection_id *excludeConnection) = 0;

        virtual bool invoke_notify_to_peer(int command, const BinaryArray &req_buff,
                                           const Q1v::CryptoNoteConnectionContext &context) = 0;

        virtual uint64_t get_connections_count() = 0;

        virtual void for_each_connection(std::function<void(Q1v::CryptoNoteConnectionContext &, PeerIdType)> f) = 0;

        // can be called from external threads
        virtual void externalRelayNotifyToAll(int command, const BinaryArray &data_buff) = 0;
    };

    struct p2p_endpoint_stub : public IP2pEndpoint {
        virtual void relay_notify_to_all(int command, const BinaryArray &data_buff,
                                         const net_connection_id *excludeConnection) override {}

        virtual bool invoke_notify_to_peer(int command, const BinaryArray &req_buff,
                                           const Q1v::CryptoNoteConnectionContext &context) override { return true; }

        virtual void
        for_each_connection(std::function<void(Q1v::CryptoNoteConnectionContext &, PeerIdType)> f) override {}

        virtual uint64_t get_connections_count() override { return 0; }

        virtual void externalRelayNotifyToAll(int command, const BinaryArray &data_buff) override {}
    };
}
