#include <Windows.h>
#include <iostream>
#include "ExecutorDLL.h"

extern "C" __declspec(dllexport) void ExecuteLuaScript(const char* script) {
    // Здесь будет код для выполнения Lua-скрипта в Roblox
    // Например, использование метода loadstring
    std::cout << "Executing Lua script: " << script << std::endl;

    // Для выполнения Lua-кода, нужно найти и использовать Roblox API
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Код, который выполняется при инъекции
        break;
    case DLL_PROCESS_DETACH:
        // Код, который выполняется при выходе
        break;
    }
    return TRUE;
}
