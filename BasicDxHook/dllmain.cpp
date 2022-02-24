#include <Windows.h>

void Init() {
    // starting point
}

BOOL APIENTRY DllMain(HMODULE a1, DWORD  a2, LPVOID a3)
{
    if (a2 == DLL_THREAD_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);
    return TRUE;
}