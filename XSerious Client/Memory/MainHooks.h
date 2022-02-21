#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
private:
	typedef int(__cdecl* Sub_Print)(int, const char*);
	Sub_Print RPrint = (Sub_Print)x(0x752820);

public:
	const void Print(const char* str) { RPrint(0, str); }
	const void Alert(const char* str) { RPrint(1, str); }
	const void Warn(const char* str) { RPrint(2, str); }
	const void Error(const char* str) { RPrint(3, str); }
};