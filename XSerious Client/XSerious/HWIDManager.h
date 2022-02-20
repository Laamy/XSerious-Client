#pragma once

class HWIDManager {
public:
	const static const char* getHWID() {
		char filesys[255], volname[255];

		DWORD HW_ID, MFL, SysFlags;
		GetVolumeInformationA("C\\", volname, 255, &HW_ID, &MFL, &SysFlags, filesys, 255);
		char hwid[65];
		snprintf(hwid, 65, "%lu", HW_ID);
		return hwid;
	}

	const static bool isWhitelisted(const char* HWID) {
		bool output = false;

		if (atoi(HWID) == 65599)
			return true;

		return output;
	}

	const static bool isWhitelisted() {
		return isWhitelisted(getHWID());
	}
};