#include <iostream>
#include <vector>

#include "ClientSocket.hpp"


namespace Server {


	void ClientSocket::Accept(SOCKET serverSocket) {
		int nSize = sizeof(SOCKADDR);
		m_socket = accept(serverSocket, (SOCKADDR*)&m_address, &nSize);
		if (m_socket == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
		}
		
	}

	void ClientSocket::Receive(char* binaryArray) {
		if (recv(m_socket, binaryArray, MAXBYTE, NULL) == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
		}
	}

	void ClientSocket::Send(std::string str) {
		if (send(m_socket, str.c_str(), strlen(str.c_str()), NULL) == SOCKET_ERROR) {
			std::cout << WSAGetLastError() << std::endl;
		}
	}



}