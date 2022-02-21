#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
public:
	typedef int(__cdecl *Sub_Print)(int, const char*);
	Sub_Print Print = (Sub_Print)x(0x752820);
};