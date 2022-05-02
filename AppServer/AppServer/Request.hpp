#pragma once

#include <vector>
#include <string>
#include <map>

namespace Server {
	class Request {
	public:
		Request(std::string req);

		void Parse(std::string req);

		std::string GetMethod();
		std::string GetPath();
		std::string GetVersion();
		std::map<std::string, std::string> GetBody();
	private:
		std::string method;
		std::string path;
		std::string version;
		std::map<std::string, std::string> body;

		std::string ParseHeader(std::string rawReq, std::vector<std::string> &dest);
		void ParseBody(std::string rawBody, std::map<std::string, std::string> &dest);

	};
}