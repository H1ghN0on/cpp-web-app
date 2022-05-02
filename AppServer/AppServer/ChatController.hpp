#pragma once
#include "ClientSocket.hpp"
#include <map>


namespace Server {
	class ChatController {
	public:
		void LogIn(ClientSocket* socket, std::map<std::string, std::string> body);
		void CheckExistence(ClientSocket* socket, std::map<std::string, std::string> body);
	};
}