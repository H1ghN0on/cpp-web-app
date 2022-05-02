#include "ChatController.hpp"
#include "Server.hpp"

#include <iostream>

namespace Server {
    void ChatController::LogIn(ClientSocket* socket, std::map<std::string, std::string> body) {
        std::string res;

        auto name = body.find("name")->second;

        if (!Server::CheckConnectionExistence(name)) {
            Server::AddConnection({ name, *socket });
            res = "HTTP/1.1 200 OK\nContent-Type: text/plain\nAccess-Control-Allow-Origin: *\ncharset=UTF-8\nContent-Length: 4\r\n\r\nDIE!";
        }
        else {
            res = "HTTP/1.1 405 OK\nContent-Type: text/plain\nAccess-Control-Allow-Origin: *\ncharset=UTF-8\nContent-Length: 14\r\n\r\nTryAnotherOne!";
        }

        if (auto sent = socket->Send(res) > 0) {
            std::cout << "Data sent" << std::endl;
        }
    }

    void ChatController::CheckExistence(ClientSocket* socket, std::map<std::string, std::string> body) {
        std::string res;

        auto name = body.find("name")->second;

        if (Server::CheckConnectionExistence(name)) {
            res = "HTTP/1.1 200 OK\nContent-Type: text/plain\nAccess-Control-Allow-Origin: *\ncharset=UTF-8\nContent-Length: 4\r\n\r\nDIE!";
        }
        else {
            res = "HTTP/1.1 405 OK\nContent-Type: text/plain\nAccess-Control-Allow-Origin: *\ncharset=UTF-8\nContent-Length: 14\r\n\r\nTryAnotherOne!";
        }

        if (auto sent = socket->Send(res) > 0) {
            std::cout << "Data sent" << std::endl;
        }
    }
}