#include "Request.hpp"

#include <vector>
#include <sstream>

namespace Server {
	
	Request::Request(std::string req) {
		Parse(req);
	}

	void Request::Parse(std::string req) {
		std::vector<std::string> params;
		std::stringstream reqStream(req);
		int i = 0;
		while (reqStream.good()) {
			params.resize(i + 1);
			reqStream >> params[i];
			++i;
		}

		method = params[0];
		path = params[1];
		version = params[2];

	}
	std::string Request::GetMethod() {
		return method;
	}
	std::string Request::GetPath() {
		return path;
	}
	std::string Request::GetVersion() {
		return version;
	}
}