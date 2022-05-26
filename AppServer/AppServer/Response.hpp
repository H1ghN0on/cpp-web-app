#pragma once
#include <string>

namespace Server {

	class Response {
	private:
		float version = 1.1f;
		int status;
		std::string type;
		std::string body;
	public:
		Response() = default;

		Response(int s, std::string t, std::string b) {
			status = s;
			type = t;
			body = b;
		}

		static std::string GenerateResponse(Response data) {
			std::string version = "HTTP/" + std::to_string(data.version);
			std::string status = std::to_string(data.status);
			std::string cors = "Access-Control-Allow-Origin: http://localhost:3000";
			std::string type = "Content-Type: " + data.type;
			std::string length = "Content-Length: " + std::to_string(data.body.length());
			std::string res = version + " " + status + "\n" + cors + "\n" + type + "\n" + length + "\r\n\r\n" + data.body + "\n";
			return res;
		}
	};

		
}