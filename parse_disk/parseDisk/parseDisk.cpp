// parseDisk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <winerror.h>

int main()
{
	//wchar_t buf[256] = L"\\\\.\\PHYSICALDRIVE1";
	wchar_t buf[256] = L"\\\\.\\PhysicalDrive1";
	HANDLE hDisk = CreateFile(buf,
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);


	if (hDisk == INVALID_HANDLE_VALUE) {
		int n = GetLastError();
		printf("error: %d\n", n);
		wchar_t err[512] = { 0 };
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, n, 0, err, 512, 0);
		printf("%S\n", err);

	}
	else {
		SetFilePointer(hDisk, 0, 0, FILE_BEGIN);

		unsigned char diskBuf[512] = { 0 };
		DWORD len = 0;
		if (FALSE == ReadFile(hDisk, diskBuf, 512, &len, 0)) {
			printf("read failed\n");
		}
		else {
			for (int i = 0, j=0; i < 512; i++,j++) {
				if (j == 32) {
					printf("\n");
					j = 0;
				}
				printf("%02x ", diskBuf[i]);	
			}
		}

		//ASSERT(hDisk != INVALID_HANDLE_VALUE);
		CloseHandle(hDisk);
	}
	

	

	char c;
	scanf_s("%c", &c);

    return 0;
}

