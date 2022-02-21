#pragma once

class EjectCommand : public Command {
public:
	EjectCommand() : Command("eject") {}

	void Execute(std::string cmd) {
		active = false;
	};
};