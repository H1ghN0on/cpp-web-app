#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <memory>

#include "Socket.hpp"

namespace Server {
	class ServerSocket: public Socket {
	public:
		ServerSocket() {};
		virtual ~ServerSocket() {};

		ServerSocket(const ServerSocket&) = delete;
		ServerSocket(ServerSocket&&) = delete;
		ServerSocket& operator=(const ServerSocket&) = delete;
		ServerSocket& operator=(ServerSocket&&) = delete;

		void Init(short family, const char* address, unsigned short port);
		void Bind();
		void Listen();

		

	private:
		sockaddr_in m_address;
	};
}