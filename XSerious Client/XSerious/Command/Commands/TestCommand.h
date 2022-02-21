#pragma once

class TestCommand : public Command {
public:
	TestCommand() : Command("test") {}

	void Execute(std::string cmd) {
		//Utils::Log("Hello world!");
		//Game::hooks.Imgui(20, 20);
	};
};