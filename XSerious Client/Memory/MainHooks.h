#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))

class MainHooks {
private:
	typedef int(__cdecl* Sub_Print)(int, const char*);
	Sub_Print RPrint = (Sub_Print)x(0x752820);

	//int __fastcall sub_5EEA80(int a1, int a2, int a3, unsigned int a4, int a5)
	typedef int(__cdecl* Sub_Print)(int a1, int a2, int a3, unsigned int a4, int a5);
	Sub_Print Print = (Sub_Print)x(0x752820);

public:
	const void Print(const char* str) { RPrint(0, str); }
	const void Alert(const char* str) { RPrint(1, str); }
	const void Warn(const char* str) { RPrint(2, str); }
	const void Error(const char* str) { RPrint(3, str); }
};