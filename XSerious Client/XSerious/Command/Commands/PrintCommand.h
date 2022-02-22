#pragma once

class PrintCommand : public Command {
public:
	PrintCommand() : Command("print") {}

	void Execute(std::string cmd) {
		std::string toPrint;
		std::cin >> toPrint;

		Utils::Log(toPrint.c_str());
	};
};