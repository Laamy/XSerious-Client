#pragma once

class TestCommand : public Command {
public:
	TestCommand() : Command("test") {}

	void Execute(std::string cmd) {
		//Utils::Log("Hello world!");
		Game::hooks.Print("This is a print");
		Game::hooks.Alert("This is an alert");
		Game::hooks.Warn("This is a warning");
		Game::hooks.Error("This is an error");
	};
};