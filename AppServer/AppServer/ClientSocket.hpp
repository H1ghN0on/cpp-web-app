#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <memory>
#include <vector>
#include "Socket.hpp"
#include <map>


namespace Server {
	class ClientSocket: public Socket {
	public:
		ClientSocket() {};
		virtual ~ClientSocket() {};

		ClientSocket(const ClientSocket& obj);

		void Accept(SOCKET serverSocket);
		int Receive(char* binaryArray);
		int Send(std::string req);

		sockaddr_in GetAddress() const;

		int SendTo(std::string str, std::map<std::string, ClientSocket> dest);

	private:
		sockaddr_in m_address;
	};
}