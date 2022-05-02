#include "Socket.hpp"

namespace Server {
	SOCKET Socket::Get() {
		return m_socket;
	}

	void Socket::Close() {
		closesocket(m_socket);
	}
}