#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
private:
	typedef void(__cdecl* Sub_Print)(int, const char*);
	Sub_Print RPrint = (Sub_Print)x(0x752820);

public:
	void Output(const char* str) { RPrint(0, str); }
	void Info(const char* str) { RPrint(1, str); }
	void Warning(const char* str) { RPrint(2, str); }
	void Error(const char* str) { RPrint(3, str); }
};