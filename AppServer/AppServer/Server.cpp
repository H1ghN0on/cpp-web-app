#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include "Request.hpp"
#include "Utils.hpp"
#include "Server.hpp"
#include "TodoController.hpp"
namespace Server {

    std::map<std::string, ClientSocket> Server::m_connected;


    BOOL WINAPI Server::ClientThread(LPVOID lpData)
    {

        
        ClientSocket* socket = (ClientSocket*)lpData;
        TodoController control;
        char binaryArray[3000] = { 0 };

        while (1)
        {
            
            int data = socket -> Receive(binaryArray);
            if (data > 0) {
                std::cout << "----------------NEXT ONE----------------" << std::endl;
                binaryArray[data] = '\0';
                std::cout << binaryArray << std::endl;
      
                Request req(binaryArray);

                const std::string path = req.GetPath();
                const auto body = req.GetBody();

                if (path == "/add-note") control.AddNote(socket, body);

                else if (path == "/get-notes") control.GetNotes(socket, body);

                else if (path == "/edit-note") control.EditNote(socket, body);

                else if (path == "/remove-note") control.RemoveNote(socket, body);

            }
            else if (data == 0) {
                continue;
            }
            else if (data == -1) {
                std::cout << WSAGetLastError() << std::endl;
            }
            
        }

        return TRUE;
    }

    void Server::AddConnection(std::map<std::string, ClientSocket>::value_type value) {
        m_connected.insert(value);
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

    bool Server::CheckConnectionExistence(std::string name) {
        for (auto& item : m_connected)
        {
            if (item.first == name) {
                return true;
            }
        }
        return false;
    }

    void Server::Listen() {

        m_serverSocket.Listen();
        std::cout << "Ready to roll" << std::endl;
        while (1) {
            HANDLE clientThread;
            DWORD dwThreadId;
            ClientSocket socket;
            socket.Accept(m_serverSocket.Get());
            if (socket.Get() == INVALID_SOCKET)
            {
                std::cout << "accept( ) failed" << std::endl;
            }
            else {

                clientThread = CreateThread(NULL, 0,
                    (LPTHREAD_START_ROUTINE)ClientThread,
                    (LPVOID)&socket, 0, &dwThreadId);

                if (clientThread == NULL)
                {
                    std::cout << "Unable to create client thread" << std::endl;
                }
                else
                {
                    CloseHandle(clientThread);
                }
            }
        }
    }
    void Server::End() {
        m_serverSocket.Close();
        
        WSACleanup();
    }
}