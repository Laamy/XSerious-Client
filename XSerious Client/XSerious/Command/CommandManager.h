#pragma once

#include "Command.h"

// commands
#include "Commands/TestCommand.h"
#include "Commands/EjectCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/ClearCommand.h"

class CommandManager {
public:
	std::vector<Command*> commands;

	void Init() {
		// Initalizing commands
		commands.push_back(new TestCommand());
		commands.push_back(new EjectCommand());
		commands.push_back(new PrintCommand());
		commands.push_back(new ClearCommand());
	}
};

CommandManager g_Cmds = CommandManager();