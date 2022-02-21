#pragma once

class Command {
public:
	std::string command;

	Command(std::string command) {
		this->command = command;
	}

	virtual void Execute(std::string cmd) {};
};