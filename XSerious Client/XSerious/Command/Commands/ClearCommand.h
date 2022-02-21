#pragma once

class ClearCommand : public Command {
public:
	ClearCommand() : Command("clear") {}

	void Execute(std::string cmd) {
		Game::ClearConsole();
	};
};