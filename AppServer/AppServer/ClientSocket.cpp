#include <iostream>

#include "ClientSocket.hpp"

#include <vector>
namespace Server {

	int ClientSocket::SendTo(std::string str, std::map<std::string, ClientSocket> dest) {


		for (const auto &socket : dest) {
			if (socket.second.Get()) {
				if (send(socket.second.Get(), str.c_str(), strlen(str.c_str()), NULL) == SOCKET_ERROR) {
					std::cout << WSAGetLastError() << std::endl;
				}
				else {
					std::cout << socket.first + " got the msg" << std::endl;
				}
			}
	
		}
		return 1;
	}

	ClientSocket::ClientSocket(const ClientSocket& obj) {
		m_socket = obj.m_socket;
		m_address = obj.m_address;
	}

	void ClientSocket::Accept(SOCKET serverSocket) {
		int nSize = sizeof(SOCKADDR);
	
		m_socket = accept(serverSocket, (SOCKADDR*)&m_address, &nSize);

		if (m_socket == SOCKET_ERROR) {
			std::cout << "Accept: " + std::to_string(WSAGetLastError()) << std::endl;
		}
		
	}

	int ClientSocket::Receive(char* binaryArray) {
		return recv(m_socket, binaryArray, 5000, NULL);
	}

	int ClientSocket::Send(std::string str) {
		return send(m_socket, str.c_str(), strlen(str.c_str()), NULL);
	}

	sockaddr_in ClientSocket::GetAddress() const {
		return m_address;
	}


}