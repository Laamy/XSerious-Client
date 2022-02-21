#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
public:
	typedef int(__cdecl *PrintHook)(int, const char*);
	PrintHook Print = (PrintHook)x(0x752820);
};