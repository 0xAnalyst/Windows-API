# Windows-API  
windows API projects that might help pentesters  

1- Reverse shell "change port and IP"  
    * it creates a socket connection bind cmd.exe in the socket  
2- CreateProc
    * Modify it with the username and password you want to use in assessment "Internal/Red Team"  
    * it uses CreateProcess twice one to add a user to the domain and second to add that users to any interesting groups you like  
3- CreateRemoteThreadInjection
it uses CreateRemoteThread to inject a DLL into the Target Process. use line 48 to change the process name and the change the DLL path to your DLL path. make sure your injecting to the right Process type like X64 into X64 bit and 32bit into 32bit depending on your compilation 



