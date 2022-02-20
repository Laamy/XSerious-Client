#pragma once

class Utils {
public:
	const static void Log(const char* str) {
		std::cout << str << std::endl;
	}

	const static void Log(const char* title, const char* str) {
		std::cout << "[" << title << "] " << str << std::endl;
	}
};