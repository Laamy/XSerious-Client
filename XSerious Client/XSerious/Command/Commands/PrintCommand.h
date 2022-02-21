#pragma once

class PrintCommand : public Command {
public:
	PrintCommand() : Command("print") {}

	void Execute(std::string cmd) {
		std::string toPrint;
		std::cin >> toPrint;

		Game::hooks.Print(toPrint.c_str());
	};
};