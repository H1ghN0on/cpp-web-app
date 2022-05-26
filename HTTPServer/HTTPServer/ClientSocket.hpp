#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <memory>

#include "Socket.hpp"


namespace Server {
	class ClientSocket: public Socket {
	public:
		ClientSocket() {};
		virtual ~ClientSocket() {};

		ClientSocket(const ClientSocket&) = delete;
		ClientSocket(ClientSocket&&) = delete;
		ClientSocket& operator=(const ClientSocket&) = delete;
		ClientSocket& operator=(ClientSocket&&) = delete;

		void Accept(SOCKET serverSocket);
		void Receive(char* binaryArray);
		void Send(std::string req);

	private:

		SOCKADDR m_address;

	};
}