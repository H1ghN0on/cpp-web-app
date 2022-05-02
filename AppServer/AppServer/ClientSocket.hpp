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

		ClientSocket(const ClientSocket& obj);

		void Accept(SOCKET serverSocket);
		int Receive(char* binaryArray);
		int Send(std::string req);
		sockaddr_in GetAddress();


	private:
		sockaddr_in m_address;
	};
}