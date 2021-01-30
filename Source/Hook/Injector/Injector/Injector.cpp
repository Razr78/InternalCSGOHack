#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcid(const char* procName)
{
    DWORD procid = 0;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hsnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hsnap, &procEntry))
        {
            do
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procid = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hsnap, &procEntry));
        }
    }
    CloseHandle(hsnap);
    return procid;
}

int main()
{
    const char* dllPath = "C:\\Users\\remra\\Desktop\\Hook.dll";
    const char* procName = "csgo.exe";
    DWORD procid = 0;

    while (!procid)
    {
        procid = GetProcid(procName);
        Sleep(30);
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procid);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (loc)
        {
            WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
        }

        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }

    if (hProc)
    {
        CloseHandle(hProc);
    }

    return 0;
}
