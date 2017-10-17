
#include "stdafx.h"
#include "windows.h"
#include <tlhelp32.h>
#include <tchar.h>
#include <comdef.h>  
#include <Strsafe.h>

BOOL InjecTargetProcess();
void AdjustIt();
LARGE_INTEGER nLargeInteger = { 0 };
HANDLE hFile;
int main(int argc, _TCHAR* argv[])
{
	AdjustIt();
	InjecTargetProcess();
	return 0;
}
BOOL InjecTargetProcess()
{

	HANDLE psnap;
	HANDLE pro;
	PBYTE shellcode;

	PROCESSENTRY32 pe32;
	char* filetoload = "C:\\test2.dll"; //DLL location 
	HANDLE hThread;
	DWORD ShellcodeLength = 0;
	psnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //take snapshot of all currently running processes 
	if (psnap == INVALID_HANDLE_VALUE)
	{
		MessageBox(0, L"Obatining Process list failed", L"Obatining Process list failed", 0);
		return(FALSE);
	}
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(psnap, &pe32)) //Retrieves information about the first process encountered in a system snapshot. 
	{
		do
		{
		
			pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID); //obtain access to the process 
			if (pro == NULL)
				continue;
			else
			{
				if (_wcsicmp(pe32.szExeFile, L"notepad.exe") == 0)
				{
					_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
					LPVOID fileremote = (LPVOID)VirtualAllocEx(pro, NULL, strlen(filetoload) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
					LPVOID pthread = (LPVOID)GetProcAddress(GetModuleHandleA(("Kernel32.dll")), "LoadLibraryA"); //loadLibary Address 
																												 //MessageBox(0, L"Memory Allocated", pe32.szExeFile, 0);
					if (fileremote != NULL)
					{

						//DWORD nOfbytes = WriteProcessMemory(pro, (LPVOID)fileremote, filetoload, strlen(filetoload)+1, NULL);  // if you using dll using this
						DWORD nOfbytes = WriteProcessMemory(pro, (LPVOID)fileremote, filetoload, strlen(filetoload) + 1, NULL);
						if (nOfbytes != 0)
						{

							if (pthread != NULL)
							{

								MessageBox(0, L"GetProcaddress succeeded", pe32.szExeFile, 0);
								hThread = CreateRemoteThread(pro, NULL, NULL, (LPTHREAD_START_ROUTINE)pthread, (LPVOID)fileremote, NULL, NULL);
								if (hThread == NULL)
								{
									LPCTSTR ErrorMessage = NULL;
									DWORD LastError = GetLastError();
									FormatMessage(
										FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
										NULL,
										LastError,
										0,
										(LPWSTR)&ErrorMessage,
										0,
										NULL);

									MessageBox(0, ErrorMessage, L"Thread Injection Failed", 0);
									WaitForSingleObject(hThread, INFINITE);

								}
							}

						}

					}
					//	}

				}
			}
		} while (Process32Next(psnap, &pe32));
	}

	return true;
}
void AdjustIt()
{
	HANDLE hToken;
	LUID luid;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	TOKEN_PRIVILEGES tkp;
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);


}
