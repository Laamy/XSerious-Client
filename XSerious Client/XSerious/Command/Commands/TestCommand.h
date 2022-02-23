#pragma once

class TestCommand : public Command {
public:
	TestCommand() : Command("test") {}

	void Execute(std::string cmd) {
		Game::hooks.ForceCrash();
	};
};