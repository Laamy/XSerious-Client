#pragma once

DWORD asdmemes;
HMODULE console;

class Game {
private:

public:
	const static MainHooks hooks;

    const static void OpenConsole(const char* title) {
        VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &asdmemes);
        *(BYTE*)(&FreeConsole) = 0xC3;
        AllocConsole();
        SetConsoleTitleA(title);
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);
        HWND ConsoleHandle = GetConsoleWindow();
        console = (HMODULE)ConsoleHandle;
        SetWindowPos(ConsoleHandle, HWND_TOP, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ShowWindow(ConsoleHandle, SW_NORMAL);
    }

    const static void CloseConsole() {
        //FreeLibraryAndExitThread(console, 0);
        FreeConsole();
    }
};

const MainHooks Game::hooks = MainHooks();