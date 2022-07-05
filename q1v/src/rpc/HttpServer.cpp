/**
 * Copyright (c) 2012-2016, The CryptoNote developers, The Bytecoin developers
 * Copyright (c) 2014-2016 XDN developers
 * Copyright (c) 2016, The Karbowanec developers
 * Copyright (c) 2017, The Niobio Cash developers
 * Copyright (c) 2021-2022, The Quan Project developers
 *
 * Full source's copyright information can be found in the "/full_copyright/old_niobiocash_3_copyright.txt"
*/

#include "HttpServer.h"
#include <boost/scope_exit.hpp>

#include <common/Base64.h>
#include <http/HttpParser.h>
#include <system/InterruptedException.h>
#include <system/TcpStream.h>
#include <system/Ipv4Address.h>

using namespace Logging;

namespace {
	void fillUnauthorizedResponse(Q1v::HttpResponse& response) {
		response.setStatus(Q1v::HttpResponse::STATUS_401);
		response.addHeader("WWW-Authenticate", "Basic realm=\"RPC\"");
		response.addHeader("Content-Type", "text/plain");
		response.setBody("Authorization required");
	}
}

namespace Q1v {

HttpServer::HttpServer(System::Dispatcher& dispatcher, Logging::ILogger& log)
  : m_dispatcher(dispatcher), workingContextGroup(dispatcher), logger(log, "HttpServer") {

}

void HttpServer::start(const std::string& address, uint16_t port, const std::string& user, const std::string& password) {
  m_listener = System::TcpListener(m_dispatcher, System::Ipv4Address(address), port);
  workingContextGroup.spawn(std::bind(&HttpServer::acceptLoop, this));

  		if (!user.empty() || !password.empty()) {
			m_credentials = Tools::Base64::encode(user + ":" + password);
		}
}

void HttpServer::stop() {
  workingContextGroup.interrupt();
  workingContextGroup.wait();
}

void HttpServer::acceptLoop() {
  try {
    System::TcpConnection connection;
    bool accepted = false;

    while (!accepted) {
      try {
        connection = m_listener.accept();
        accepted = true;
      } catch (System::InterruptedException&) {
        throw;
      } catch (std::exception&) {
        // try again
      }
    }

    m_connections.insert(&connection);
    BOOST_SCOPE_EXIT_ALL(this, &connection) {
      m_connections.erase(&connection); };

	workingContextGroup.spawn(std::bind(&HttpServer::acceptLoop, this));

	//auto addr = connection.getPeerAddressAndPort();
	auto addr = std::pair<System::Ipv4Address, uint16_t>(static_cast<System::Ipv4Address>(0), 0);
	try {
		addr = connection.getPeerAddressAndPort();
	} catch (std::runtime_error&) {
		logger(WARNING) << "Could not get IP of connection";
	}

    logger(DEBUGGING) << "Incoming connection from " << addr.first.toDottedDecimal() << ":" << addr.second;

    System::TcpStreambuf streambuf(connection);
    std::iostream stream(&streambuf);
    HttpParser parser;

    for (;;) {
      HttpRequest req;
      HttpResponse resp;
	  resp.addHeader("Access-Control-Allow-Origin", "*");

      parser.receiveRequest(stream, req);
				if (authenticate(req)) {
					processRequest(req, resp);
				}
				else {
					logger(WARNING) << "Authorization required " << addr.first.toDottedDecimal() << ":" << addr.second;
					fillUnauthorizedResponse(resp);
				}

      stream << resp;
      stream.flush();

      if (stream.peek() == std::iostream::traits_type::eof()) {
        break;
      }
    }

    logger(DEBUGGING) << "Closing connection from " << addr.first.toDottedDecimal() << ":" << addr.second << " total=" << m_connections.size();

  } catch (System::InterruptedException&) {
  } catch (std::exception& e) {
    logger(WARNING) << "Connection error: " << e.what();
  }
}

	bool HttpServer::authenticate(const HttpRequest& request) const {
		if (!m_credentials.empty()) {
			auto headerIt = request.getHeaders().find("authorization");
			if (headerIt == request.getHeaders().end()) {
				return false;
			}

			if (headerIt->second.substr(0, 6) != "Basic ") {
				return false;
			}

			if (headerIt->second.substr(6) != m_credentials) {
				return false;
			}
		}

		return true;
	}

}
