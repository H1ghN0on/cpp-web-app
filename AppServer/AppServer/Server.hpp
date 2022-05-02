#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <memory>
#include <map>

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
		static void AddConnection(std::map<std::string, ClientSocket>::value_type value);

		static std::map<std::string, ClientSocket> m_connected;
		static std::map<std::string, std::string> m_messages;

		static BOOL WINAPI ClientThread(LPVOID lpData);
		static bool CheckConnectionExistence(std::string name);
	private:
		ServerSocket m_serverSocket;
		WSADATA wsaData;
		
		
		
	};
}