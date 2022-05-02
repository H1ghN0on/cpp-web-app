#pragma once

#include <string>

namespace Server {
	class Request {
	public:

		Request(std::string req);

		void Parse(std::string req);
		std::string GetMethod();
		std::string GetPath();
		std::string GetVersion();

	private:
		std::string method;
		std::string path;
		std::string version;
	};
}