/**
 * Copyright (c) 2016-2019, The Karbo developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/karbo_copyright.txt"
*/

#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <sstream>
#include <functional>
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <boost/program_options/variables_map.hpp>
#include <iostream>

#include <arpa/nameser.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <resolv.h>
#include <netdb.h>
#include <unistd.h>

#include "DnsTools.h"

namespace Common {

    bool fetch_dns_txt(const std::string domain, std::vector<std::string> &records) {
        using namespace std;

        res_init();
        ns_msg nsMsg;
        int response;
        unsigned char query_buffer[1024];
        {
            ns_type type = ns_t_txt;

            const char *c_domain = (domain).c_str();
            response = res_query(c_domain, 1, type, query_buffer, sizeof(query_buffer));

            if (response < 0)
                return 1;
        }

        ns_initparse(query_buffer, response, &nsMsg);
        map<ns_type, function<void(const ns_rr &rr)>> callbacks;
        callbacks[ns_t_txt] = [&nsMsg, &records](const ns_rr &rr) -> void {
            int txt_len = *(unsigned char *) ns_rr_rdata(rr);
            char txt[256];
            memset(txt, 0, 256);
            if (txt_len <= 255) {
                memcpy(txt, ns_rr_rdata(rr) + 1, txt_len);
                records.push_back(txt);
            }
        };
        for (int x = 0; x < ns_msg_count(nsMsg, ns_s_an); x++) {
            ns_rr rr;
            ns_parserr(&nsMsg, ns_s_an, x, &rr);
            ns_type type = ns_rr_type(rr);
            if (callbacks.count(type)) {
                callbacks[type](rr);
            }
        }
        if (records.empty()) {
            return false;
        }

        return true;
    }

}
