#pragma once

#define x(x) (x - 0x400000 + (DWORD)GetModuleHandleA(0))
#include "SDK/SubSDK/TextHolder.h"

DWORD ansnenen;

class MainHooks {
private:
	typedef void(__cdecl* Sub_Crash)(int);
	Sub_Crash RCrash = (Sub_Crash)x(0x700000); // used to force a crash

	typedef void(__cdecl* Sub_Print)(int, const char*);
	Sub_Print RPrint = (Sub_Print)x(0x752820);

	typedef void(__cdecl* Sub_FCrash)(int, const char*);
	Sub_FCrash FCrash = (Sub_FCrash)x(0x1CAF720);

	uintptr_t Base = (uintptr_t)GetModuleHandleA("RobloxPlayerBeta.exe");

	TextHolder* crashTitleAddr = reinterpret_cast<TextHolder*>(0x2A7CB68);
	TextHolder* crashMsgAddr = reinterpret_cast<TextHolder*>((uintptr_t)crashTitleAddr - 0x48);
	TextHolder* crashMsgSubAddr = reinterpret_cast<TextHolder*>((uintptr_t)crashTitleAddr + 0x38);
	
	// 0x208D880 Pushboolean
public:
	void Output(const char* str) { RPrint(0, str); }
	void Info(const char* str) { RPrint(1, str); }
	void Warning(const char* str) { RPrint(2, str); }
	void Error(const char* str) { RPrint(3, str); }

	void ForceCrash() { RCrash(0x10F2C); } // funny number

	void SetCrashMsg(const char* title, const char* msg) {
		//VirtualProtect((PVOID)crashMsgAddr, 216, PAGE_EXECUTE_READWRITE, &ansnenen);

		//crashTitleAddr->setText("Hello!");
	}
};