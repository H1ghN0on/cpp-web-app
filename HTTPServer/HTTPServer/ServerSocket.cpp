#include <iostream>

#include "ServerSocket.hpp"

namespace Server {
	void ServerSocket::Init(short family, const char* address, unsigned short port) {
		
		m_socket = socket(family, SOCK_STREAM, IPPROTO_TCP);
		memset(&m_address, 0, sizeof(m_address));

		m_address.sin_family = family;
		m_address.sin_addr.s_addr = inet_addr(address);
		m_address.sin_port = htons(port);
	}

	void ServerSocket::Bind() {
		bind(m_socket, (SOCKADDR*)&m_address, sizeof(SOCKADDR));
	}

	void ServerSocket::Listen() {
		listen(m_socket, 20);
	}

}