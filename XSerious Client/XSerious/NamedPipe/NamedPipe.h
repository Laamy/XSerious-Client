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

		//Utils::Log("DEBUG", "Running PIPE");
		while (hp != INVALID_HANDLE_VALUE && active) {
		resetPipe:
			if (ConnectNamedPipe(hp, NULL) != FALSE)   // thanks stack <3 https://stackoverflow.com/questions/26561604/create-named-pipe-c-windows
			{
				Utils::Log("DEBUG", "Connected to pipe!");
				while (ReadFile(hp, buffer, sizeof(buffer) - 1, &dr, NULL) != FALSE)
				{
					buffer[dr] = '\0';
					try
					{
						data = data + buffer;
					}
					catch (...) {}
				}
				// parse data

				Utils::Log(data.c_str());
			}
			goto resetPipe;

			DisconnectNamedPipe(hp);
		}
		Utils::Log("DEBUG", "Disconnected from PIPE");
		Utils::Log("DEBUG", "Fatal ERROR (Please restart your PC)!");
	}
};