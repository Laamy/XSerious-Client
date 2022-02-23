#pragma once

DWORD asdmemes;
HMODULE console;

class Game {
private:

public:
	static MainHooks hooks;
    static FILE* fp;

    static BYTE tmpByte[4];

    const static void RetFreeConsole() {
        uintptr_t* bytes = reinterpret_cast<uintptr_t*>(&FreeConsole);
        VirtualProtect((PVOID)bytes, 4, PAGE_EXECUTE_READWRITE, &asdmemes);

        tmpByte[0] = bytes[0];
        tmpByte[1] = bytes[1];
        tmpByte[2] = bytes[2];
        tmpByte[3] = bytes[3];

        bytes[0] = 0xC3;
        bytes[1] = 0x90;
        bytes[2] = 0x90;
        bytes[3] = 0x90;
    }
    const static void UnRetFreeConsole() {
        uintptr_t* bytes = reinterpret_cast<uintptr_t*>(&FreeConsole);
        VirtualProtect((PVOID)bytes, 4, PAGE_EXECUTE_READWRITE, &asdmemes);

        bytes[0] = bytes[0];
        bytes[1] = bytes[1];
        bytes[2] = bytes[2];
        bytes[3] = bytes[3];
    }
    const static void OpenConsole(const char* title) {
        RetFreeConsole();

        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONIN$", "r", stdin);

        SetConsoleTitleA(title);

        SetWindowPos(GetConsoleWindow(), HWND_TOP, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
        ShowWindow(GetConsoleWindow(), SW_NORMAL);
    }
    const static void CloseConsole() {
        UnRetFreeConsole();
        FreeConsole();
    }
    const static void ClearConsole() {
        system("cls"); // unsafe
    }
};

FILE* Game::fp = new FILE();
BYTE Game::tmpByte[4] = { 0x90, 0x90, 0x90, 0x90 };
MainHooks Game::hooks = MainHooks();    