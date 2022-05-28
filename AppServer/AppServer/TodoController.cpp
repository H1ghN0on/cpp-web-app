#include "TodoController.hpp"
#include "Server.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "TodoController.hpp"

#include "Server.hpp"
#include "Utils.hpp"

#include "Response.hpp"

namespace Server {

	class Item {
		Item(int p_id, std::string p_name, bool p_isChecked) {
			id = p_id;
			name = p_name;
			isChecked = p_isChecked;
		}
		int id;
		std::string name;
		bool isChecked;
	};

	std::string CastNotesToJson(std::vector<std::map<std::string, std::string>> items) {
		std::string json = "{\"notes\":[";
		for (auto& item : items) {
			json += "{";
			for (auto& row : item) {
				std::string field = '"' + row.first + '"';
				std::string value = '"' + row.second + '"';
				json += field + ":" + value + ",";
			}
			json.pop_back();
			json += "},";
		}
		if (items.size() != 0) {
			json.pop_back();
		}
		json += "]}";

		

		return json;
	}


	void TodoController::AddNote(ClientSocket* socket, std::map<std::string, std::string> body) {
		const std::string name = body.find("name")->second;
		const std::string text = body.find("text")->second;


		std::ifstream idb("notes.txt");
		bool isFound = false;
		int id = 0;
		if (idb.is_open()) {
			std::ofstream odb("notes-tmp.txt");
			std::string line;
			while (std::getline(idb, line)) {
				if (line == "") {
					continue;
				}
				auto words = Utils::Split(line, "&");
				if (words[0] == "user=" + name) {
					id = stoi(Utils::Split(words[1], "=")[1]);
					std::string userData = words[0] + "&" + "length=" + std::to_string(id + 1);
					odb << userData << std::endl;
					isFound = true;
					
				}
				else if (isFound) {
					std::string i_id = "id=" + std::to_string(id + 1);
					std::string i_text = "text=" + text;
					std::string i_checked = "isChecked=false";

					if (id == 0) {
						odb << i_id + "&" + i_text + "&" + i_checked << std::endl;
						odb << line << std::endl;
					}
					else {

						for (int j = 0; j < id; j++) {
							
							odb << line << std::endl;
							std::getline(idb, line);
						}

						odb << i_id + "&" + i_text + "&" + i_checked << std::endl;

						odb << line << std::endl;
						odb.flush();
					}
					isFound = false;
				}
				else {
					odb << line << std::endl;
					odb.flush();
				};
				
			}
			if (isFound) {
				std::string i_id = "id=" + std::to_string(id + 1);
				std::string i_text = "text=" + text;
				std::string i_checked = "isChecked=false";
				odb << i_id + "&" + i_text + "&" + i_checked << std::endl;
			}
			idb.close();
			odb.close();
			std::remove("notes.txt");
			auto status = std::rename("notes-tmp.txt", "notes.txt");


			Response resData(200, "text/plain; ; charset=UTF-8", "Added!");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "AddNote: Data sent" << std::endl;
			};
		}
		else {
			idb.close();
			Response resData(405, "text/plain; ; charset=UTF-8", "Error occured on the server");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "AddNote: Data sent" << std::endl;
			};
		}

	}

	void TodoController::GetNotes(ClientSocket* socket, std::map<std::string, std::string> body) {
		const std::string name = body.find("name") -> second;
		std::map<std::string, std::string> item;
		std::vector<std::map<std::string, std::string>> items;
		std::ifstream db("notes.txt");
		bool isFound = false;
		bool isReallyFound = false;
		if (db.is_open()) {
			std::string line;
			while (std::getline(db, line)) {
				auto words = Utils::Split(line, "&");

				if (words[0] == "user=" + name) {
					isFound = true;
					isReallyFound = true;
				}

				else if (isFound) {
					if (!words[0].rfind("user=", 0)) {
						std::cout << words[0] << std::endl;
						break;
					}
					item.clear();
					auto words = Utils::Split(line, "&");
					for (auto word : words) {
						auto values = Utils::Split(word, "=");
						item.insert({values[0], values[1]});
					}

					items.push_back(item);
				}
				
			}
			db.close();
			if (!isReallyFound) {
				std::ofstream mb("notes.txt", std::ios::app);
				mb << "user=" + name + "&length=0" << std::endl;
				mb.close();

			}
			auto json = CastNotesToJson(items);

			Response resData(200, "text/plain; ; charset=UTF-8", json);
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "GetNotes: Data sent" << std::endl;
			};
	
		}
		else {
			Response resData(405, "text/plain; ; charset=UTF-8", "Error occured on the server");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "GetNotes: Data sent" << std::endl;
			};
		}

		


	}

	void TodoController::EditNote(ClientSocket* socket, std::map<std::string, std::string> body) {
		const std::string name = body.find("name")->second;
		const std::string id = body.find("id")->second;
		const std::string text = body.find("text")->second;
		const std::string field = body.find("field")->second;
		bool isFound = false;
		int length;
		std::ifstream idb("notes.txt");

		if (idb.is_open()) {
			std::ofstream odb("notes-tmp.txt");
			std::string line;
			while (std::getline(idb, line)) {
				if (line == "") {
					continue;
				}
				auto words = Utils::Split(line, "&");
				if (words[0] == "user=" + name) {
					length = stoi(Utils::Split(words[1], "=")[1]);

					odb << line << std::endl;
					odb.flush();
					isFound = true;
				}
				else if (isFound) {
					for (int j = 0; j < length; j++) {
						auto values = Utils::Split(line, "&");
						if (values[0] == "id=" + id) {
							if (field == "isChecked") {
								line = values[0] + "&" + values[1] + "&" + "isChecked=" + text;
							}
							else if (field == "text") {
								line = values[0] + "&" + "text=" + text + "&" + values[2];
							}
							
						}
						odb << line << std::endl;
						odb.flush();
						std::getline(idb, line);
					}
					odb << line << std::endl;
					odb.flush();
					isFound = false;
				}
				else {
					odb << line << std::endl;
					odb.flush();
				};

			}
			idb.close();
			odb.close();
			std::remove("notes.txt");
			auto status = std::rename("notes-tmp.txt", "notes.txt");


			Response resData(200, "text/plain; ; charset=UTF-8", "Removed!");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "EditNote: Data sent" << std::endl;
			};
		}
		else {
			idb.close();
			Response resData(405, "text/plain; ; charset=UTF-8", "Error occured on the server");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "EditNote: Data sent" << std::endl;
			};
		}
	}

	void TodoController::RemoveNote(ClientSocket* socket, std::map<std::string, std::string> body) {

		const std::string name = body.find("name")->second;
		const std::string id = body.find("id")->second;
		bool isFound = false;
		bool isIdFound = false;
		bool isReallyFound = false;
		int length;
		std::ifstream idb("notes.txt");
		
		if (idb.is_open()) {
			std::ofstream odb("notes-tmp.txt");
			std::string line;
			while (std::getline(idb, line)) {

				auto words = Utils::Split(line, "&");
				if (words[0] == "user=" + name) {
					length = stoi(Utils::Split(words[1], "=")[1]);
					std::string userData = words[0] + "&" + "length=" + std::to_string(length - 1);
					odb << userData << std::endl;
					isFound = true;
					isReallyFound = true;
				}
				else if (isFound && length != 0) {
					
					for (int j = 0; j < length; j++) {
						auto values = Utils::Split(line, "&");
						if (values[0] == "id=" + id) {
							isIdFound = true;
						}

						else {
							if (isIdFound) {
								line = "id=" + std::to_string(j) + "&" + values[1] +  "&" + values[2];
							}
							odb << line << std::endl;
							odb.flush();
						} 
						std::getline(idb, line);
					}
					odb << line << std::endl;
		
					isFound = false;
				}
				else {
					odb << line << std::endl;
				};

			}
			idb.close();
			odb.close();
			std::remove("notes.txt");
			auto status = std::rename("notes-tmp.txt", "notes.txt");

			Response resData(200, "text/plain; ; charset=UTF-8", "Removed!");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "RemoveNote: Data sent" << std::endl;
			};
		}
		else {
			idb.close();
			Response resData(405, "text/plain; ; charset=UTF-8", "Error occured on the server");
			if (socket->Send(Response::GenerateResponse(resData)) > 0) {
				std::cout << "RemoveNote: Data sent" << std::endl;
			};
		}

	}

}