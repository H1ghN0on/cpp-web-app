#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <memory>

namespace Server {
	class Socket {
	public:
		Socket() {};
		virtual ~Socket() {};

		Socket(const Socket&) = delete;
		Socket(Socket&&) = delete;
		Socket& operator=(const Socket&) = delete;
		Socket& operator=(Socket&&) = delete;

		SOCKET Get() const;
		void Close();

	protected:
		SOCKET m_socket;
	};
}