#pragma once
#include "ClientSocket.hpp"

#include <vector>
#include <map>


namespace Server {


	class TodoController {
	public:
		TodoController() = default;

		void AddNote(ClientSocket* socket, std::map<std::string, std::string> body);

		void GetNotes(ClientSocket* socket, std::map<std::string, std::string> body);

		void EditNote(ClientSocket* socket, std::map<std::string, std::string> body);

		void RemoveNote(ClientSocket* socket, std::map<std::string, std::string> body);
	private:

	};

}