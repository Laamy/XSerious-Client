#pragma region Imports

// Include system imports
#include <WinSock2.h>
#include <vector>
#include <Psapi.h>
#include <iostream>
#include <Windows.h>

// Include utils
#include "XSerious/Utils/Mem.h"
#include "XSerious/Utils/Utils.h"

// Include XSerious vUtils
#include "XSerious/HWIDManager.h"

// Include game class
#include "Memory/Game.h"

#pragma endregion

HMODULE Dll_hModule;

DWORD __stdcall Eject(LPVOID a1) {
    Sleep(100);
    FreeLibraryAndExitThread(Dll_hModule, 0);
}

DWORD WINAPI Init() {
    AllocConsole();

    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    
    Utils::Log("Getting HWID...");
    Utils::Log(HWIDManager::getHWID());

    while (true) {
        Sleep(50);
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }

    fclose(fp);
    FreeConsole();
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
} // test comment