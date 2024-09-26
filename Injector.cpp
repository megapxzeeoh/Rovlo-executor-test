#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "Injector.h"

DWORD GetProcessId(const char* processName) {
    DWORD processID = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_PROCESS, 0);
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    while (Process32Next(snapshot, &processEntry)) {
        if (strcmp(processEntry.szExeFile, processName) == 0) {
            processID = processEntry.th32ProcessID;
            break;
        }
    }
    CloseHandle(snapshot);
    return processID;
}

void InjectDLL(DWORD processID, const char* dllPath) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (hProcess) {
        LPVOID pDllPath = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        WriteProcessMemory(hProcess, pDllPath, (LPVOID)dllPath, strlen(dllPath) + 1, NULL);

        HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, 
            (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"), 
            pDllPath, 0, NULL);
        CloseHandle(hThread);
        VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
    }
    CloseHandle(hProcess);
}

int main() {
    const char* dllPath = "C:\\path\\to\\your\\ExecutorDLL.dll"; // Укажи путь к DLL
    DWORD processID = GetProcessId("RobloxPlayerBeta.exe"); // Укажи имя процесса Roblox

    if (processID) {
        InjectDLL(processID, dllPath);
        std::cout << "DLL injected successfully!" << std::endl;
    } else {
        std::cout << "Failed to find Roblox process." << std::endl;
    }
    return 0;
}
