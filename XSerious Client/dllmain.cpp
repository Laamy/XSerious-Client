#pragma region Imports

#define _CRT_SECURE_NO_DEPRICATE
#define _CRT_SECURE_NO_WARNINGS

// Include system imports
#include <WinSock2.h>
#include <vector>
#include <Psapi.h>
#include <iostream>
#include <Windows.h>

// Include XSerious vUtils
#include "XSerious/HWIDManager.h"

// Include game class
#include "Memory/MainHooks.h"
#include "Memory/Game.h"

// Include utils
#include "XSerious/Utils/Mem.h"
#include "XSerious/Utils/Utils.h"

bool active = true;

// Include command manager
#include "XSerious/Command/CommandManager.h"

#pragma endregion

HMODULE Dll_hModule;

DWORD __stdcall Eject(LPVOID a1) {
    Sleep(100);
    FreeLibraryAndExitThread(Dll_hModule, 0);
}

DWORD WINAPI Init() {
    const char* name = "XSerious";
    Game::OpenConsole(name);

    Utils::Log(name, "Attempting to inject...");
    g_Cmds.Init();

    while (active) {
        std::string command;
        std::cin >> command;

        for (Command* cmd : g_Cmds.commands) { // console commands
            if (cmd->command == command)
                cmd->Execute(command);
        }
    }

    Game::CloseConsole();

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Eject, 0, 0, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE a1, DWORD  a2, LPVOID a3) {
    if (a2 == DLL_PROCESS_ATTACH)
    {
        Dll_hModule = a1;
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);
    }
    return TRUE;
}