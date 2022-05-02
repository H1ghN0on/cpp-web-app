#pragma once

#include <vector>
#include <string>


namespace Server {
	static class Utils {
	private:
		static inline std::string& Rtrim(std::string& s, const char* t = " ");
		static inline std::string& Ltrim(std::string& s, const char* t = " ");
	public:

		static inline std::string& Trim(std::string& s, const char* t = " ");
		static std::vector<std::string> Split(std::string word, const char* symbol);
	};
}
