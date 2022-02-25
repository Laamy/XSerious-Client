#pragma once

class NamedPipe {
public:
	static void InitalizePipeServer() {
		std::string data = "";
		HANDLE hp;
		char buffer[0xF4240];
		DWORD dr;
		hp = CreateNamedPipe(TEXT("\\\\.\\pipe\\XSeries"),
			PIPE_ACCESS_DUPLEX,
			PIPE_WAIT | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 0xF4240, 0xF4240, NMPWAIT_USE_DEFAULT_WAIT, 0);

		while (hp != INVALID_HANDLE_VALUE)
		{
			if (ConnectNamedPipe(hp, NULL) != FALSE)   // wait for someone to connect to the pipe
			{
				while (ReadFile(hp, buffer, sizeof(buffer) - 1, &dr, NULL) != FALSE)
				{
					/* add terminating zero */
					buffer[dr] = '\0';

					LuaManager::Execute(buffer); // execute the buffer
				}
			}

			DisconnectNamedPipe(hp);
		}
		Utils::Log("DEBUG", "Disconnected from PIPE");
		Utils::Log("DEBUG", "Fatal ERROR (Please restart your PC)!");
	}
};