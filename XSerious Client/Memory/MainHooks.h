#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
public:
	typedef void(__thiscall* TestHook)();
	TestHook _Test;
};