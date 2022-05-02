#include <iostream>

#include "ClientSocket.hpp"


namespace Server {

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

	sockaddr_in ClientSocket::GetAddress() {
		return m_address;
	}

}