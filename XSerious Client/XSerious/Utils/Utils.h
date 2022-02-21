#pragma once

class Utils {
public:
	const static void Log(const char* str) {
		std::cout << str << std::endl;
		Game::hooks.Print(str);
	}

	const static void Log(const char* title, const char* str) {
		std::string s1("[");
		std::string s2("] ");

		std::string Output(s1 + title + s2 + str); // there has to be a better way to do this ;-;

		Utils::Log(Output.c_str());
	}
};