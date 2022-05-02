#include "Request.hpp"
#include "Utils.hpp"

#include <sstream>
#include <iostream>
namespace Server {
	Request::Request(std::string req) {
        Parse(req);
	}

    //Returns body string
    std::string Request::ParseHeader(std::string rawReq, std::vector<std::string> &dest) {
        std::stringstream reqStream(rawReq);
        std::string bodyStr;

        int i = 0;
        while (reqStream.good()) {
            dest.resize(i + 1);
            reqStream >> dest[i];
            if (dest[i] == "body?") {
                std::getline(reqStream, bodyStr);
                break;
            }
            ++i;
        }
        return bodyStr;
    }

    void Request::ParseBody(std::string rawBody, std::map<std::string, std::string> &dest) {

        auto items = Utils::Split(rawBody, "&");
        for (auto item : items) {
            auto values = Utils::Split(item, "=");
            dest.insert({ values[0], values[1] });
        }

    }

	void Request::Parse(std::string req) {

        std::vector<std::string> params;
        std::map<std::string, std::string> body;

        ParseBody(ParseHeader(req, params), body);
        
        

        this->method = params[0];
        this->path = params[1];
        this->version = params[2];
        this->body = body;
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
	std::map<std::string, std::string> Request::GetBody() {
		return body;
	}
}