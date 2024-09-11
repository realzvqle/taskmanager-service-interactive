#include <windows.h>
#include <winnt.h>
#include <winsvc.h>
#include <winuser.h>



void ShowFormattedMessageBox(DWORD errorCode)
{
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    MessageBox(
        NULL,
        (LPCTSTR)lpMsgBuf,
        TEXT("Error"),
        MB_OK | MB_ICONERROR);

    LocalFree(lpMsgBuf);
}



void _entry(){
    HANDLE hSC = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(!hSC){
        ShowFormattedMessageBox(GetLastError());
        ExitProcess(-1);
    }
    HANDLE hService = CreateService(hSC, 
              "idk", 
              "poo", 
              SC_MANAGER_ALL_ACCESS, 
              SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, 
              SERVICE_DEMAND_START, 
              SERVICE_ERROR_SEVERE, 
              "C:\\Windows\\system32\\taskmgr.exe", 
              NULL, NULL, NULL, NULL, NULL);
    if(!hService){
        ShowFormattedMessageBox(GetLastError());
        ExitProcess(-1);
    }

    StartService(hService, 0, NULL);


    ExitProcess(0);
}

