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

// what else do u think tjhis is for u sutpid fuck
#include "XSerious/LuaEnvironment/lua_x.h"

// Include pipe header
#include "XSerious/NamedPipe/NamedPipe.h"


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

    Game::hooks.SetCrashMsg("XSerious Crash", "Test crash msg"); // customize crash message

    NamedPipe::InitalizePipeServer(); // lua & pipe shit
    LuaManager::InitalizeLua();
    
    g_Cmds.Init(); // initalize console commands

    Utils::Log(name, "Injected!");

    while (active) {
        std::string command;
        std::cin >> command;

        for (Command* cmd : g_Cmds.commands) {
            if (cmd->command == command) {
                cmd->Execute(command);
            }
        }
    }

    Game::CloseConsole(); // close console

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