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
#include <arpa/inet.h>

#include "DnsTools.h"

namespace Common {

    static size_t calcrr(int q, const u_char *p, size_t l, size_t t) {
        while (l < t) {
            if ((p[l] & 0xc0) == 0xc0) {
                l += 2;
            } else if (p[l] & 0xc0) {
                l += 1;
            } else if (p[l]) {
                l += p[l];
            } else {
                break;
            }
        }
        l += 4; /* type + class */
        if (q)
            return l;
        l += 6; /* ttl + rdlength */
        if (l < t) {
            l += (p[l - 2] << 8) + p[l - 1]; /* rdata */
        }
        return l;
    }

    size_t calcdnslen(const u_char *dnspkt, size_t dnslen) {
        HEADER dns;
        size_t n, len;

        if (dnslen > 65535 || dnslen < sizeof(dns)) {
            return 0;
        }
        memcpy(&dns, dnspkt, sizeof dns);
        len = sizeof(dns);

        for (n = 0; len < dnslen && n < dns.qdcount; n++) {
            len = calcrr(1, dnspkt, len, dnslen);
        }
        for (n = 0; len < dnslen && n < dns.ancount; n++) {
            len = calcrr(0, dnspkt, len, dnslen);
        }
        for (n = 0; len < dnslen && n < dns.nscount; n++) {
            len = calcrr(0, dnspkt, len, dnslen);
        }
        for (n = 0; len < dnslen && n < dns.arcount; n++) {
            len = calcrr(0, dnspkt, len, dnslen);
        }
        if (len < dnslen)
            return len;
        return dnslen;
    }

    bool fetch_dns_txt(const std::string domain, std::vector<std::string> &records) {
        using namespace std;

        unsigned char buf[6390];
        res_init();
        int len = res_query(domain.c_str(), C_IN, ns_t_txt, buf, sizeof(buf));
        if (len < 0) {
            perror("res_query");
            return false;
        }
        ns_msg msg;

        if (ns_initparse(buf, len, &msg) < 0) {
            if (errno == EMSGSIZE) {
                size_t dnslen = calcdnslen(buf, len);
                if (((int) dnslen > 0) && ((int) len > (int) dnslen) && (ns_initparse(buf, (int) dnslen, &msg) < 0)) {
                    cerr << strerror(errno) << endl;
                    return false;
                }
            } else {
                cerr << strerror(errno) << endl;
                return false;
            }
        }
        map<ns_type, function<void(const ns_rr &rr)>> callbacks;
        callbacks[ns_t_txt] = [&records](const ns_rr &rr) -> void {
            int txt_len = *(unsigned char *) ns_rr_rdata(rr);
            char txt[256];
            memset(txt, 0, 256);
            if (txt_len <= 255) {
                memcpy(txt, ns_rr_rdata(rr) + 1, txt_len);
                records.emplace_back(txt);
            }
        };
        //
        for (int x = 0; x < ns_msg_count(msg, ns_s_an); x++) {
            ns_rr rr;
            if (ns_parserr(&msg, ns_s_an, x, &rr) < 0) {
                continue;
            }
            ns_type type = ns_rr_type(rr);
            if (callbacks.count(type)) {
                callbacks[type](rr);
            }
        }
        //
        if (records.empty()) {
            return false;
        }
        return true;
    }
}
