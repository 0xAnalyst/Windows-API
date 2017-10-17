# Windows-API  
Windows API projects that might help pentesters  

## Reverse shell "Change IP and Port"  
     It creates a socket connection and bind cmd.exe in the socket  
## CreateProc
     Modify it with the username and password you want to use in assessment "Internal/Red Team"  
     It uses CreateProcess twice one to add a user to the domain and second to add that users to any interesting groups you like  
## CreateRemoteThreadInjection
     It uses CreateRemoteThread to inject a DLL into the Target Process. use line 48 to change the process name and the change the DLL path to your DLL path. make sure your injecting to the right Process type like X64 into X64 bit and 32bit into 32bit depending on your compilation
     It reads all processes on the system and tries to find notepad.exe and inject to it. you can modify it with a line of code change to try to inject to all process on the system



