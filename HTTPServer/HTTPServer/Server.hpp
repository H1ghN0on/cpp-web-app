#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <memory>

#include "Socket.hpp"
#include "ClientSocket.hpp"
#include "ServerSocket.hpp"


namespace Server {
	class Server {
	public:
		Server() {};
		virtual ~Server() {};

		Server(const Server&) = delete;
		Server(Server&&) = delete;
		Server& operator=(const Server&) = delete;
		Server& operator=(Server&&) = delete;

		
		int Start(const char* address, unsigned short port);
		void Listen();
		void End();




	private:
		ClientSocket m_clientSocket;
		ServerSocket m_serverSocket;
		WSADATA wsaData;
			


		char binaryArray[MAXBYTE] = { 0 };
	};
}