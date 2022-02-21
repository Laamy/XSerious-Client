#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
public:
	typedef int(__cdecl *RPrint)(int, const char*, ...);
	RPrint Print = (RPrint)x(0x752820);

	typedef unsigned int(__stdcall *RImGui)(int a1, int a2, ...);
	RImGui Imgui = (RImGui)x(0x13DC240);
};