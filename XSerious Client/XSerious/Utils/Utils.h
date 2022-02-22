#pragma once

class Utils {
public:
	const static void Log(const char* str) {
		std::cout << str << std::endl;
		Game::hooks.Output(str);
	}
	const static void Log(const char* title, const char* str) {
		std::string s1("[");
		std::string s2("] ");

		std::string Output(s1 + title + s2 + str); // I'll make merge func later

		Utils::Log(Output.c_str());
	}

	const static std::vector<const char*> Split(const char* myString, const char* tso) {
		std::string myStr = std::string(myString);
		std::string _tso = std::string(tso);

		size_t start = 0, end, tso_len = _tso.length();
		std::vector<const char*> output;
		std::string subT;


		while ((end = myStr.find(tso, start)) != std::string::npos) {
			subT = myStr.substr(start, end - start);
			start = end + tso_len;
			output.push_back(subT.c_str());
		}

		output.push_back(myStr.substr(start).c_str());

		return output;
	}
};