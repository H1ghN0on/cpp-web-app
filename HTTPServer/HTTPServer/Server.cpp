#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Request.hpp"
#include "Server.hpp"

namespace Server {

    std::string parseType(std::string path) {
        std::string ext = path;
        std::vector<std::string> words;
        char* pch = strtok((char*)ext.c_str(), ".");
        while (pch != nullptr) {
            words.push_back(pch);
            pch = strtok(NULL, ".");
        }

        std::string type = "text/html";


        if (words.back() == "css") {
            type = "text/css";
        }
        else if (words.back() == "js") {
            type = "text/javascript";
        } 
        else if (words.back() == "ico") {
            type = "image/x-icon";
        }
        return type;
    }

    std::string readHTML(std::string path) {
        std::ifstream f(path);
        std::stringstream html;
        html << f.rdbuf();
        return html.str();
    }

	int Server::Start(const char* address, unsigned short port) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cout << "WSAData initialize terminated" << std::endl;
            return 1;
        };

        m_serverSocket.Init(PF_INET, address, port);
        m_serverSocket.Bind();
	}

    void Server::Listen() {
        

        m_serverSocket.Listen();
        while (1) {
            std::cout << "Pending..." << std::endl;
            m_clientSocket.Accept(m_serverSocket.Get());
            m_clientSocket.Receive(binaryArray);


            Request req(binaryArray);

            std::string path = req.GetPath();
            std::string type = parseType(path);

            

            std::string html = readHTML(path.substr(1));
            std::cout << path << std::endl;
            std::string res = "HTTP/1.1 200 OK\nContent-Type: " + type + "; charset=UTF-8\nContent-Length: " + std::to_string(html.length()) + "\r\n\r\n" + html + "\n";
            std::cout << res << std::endl;
            m_clientSocket.Send(res);
           
            
        }
    }
    void Server::End() {
        m_serverSocket.Close();
        m_clientSocket.Close();
        WSACleanup();
    }
}