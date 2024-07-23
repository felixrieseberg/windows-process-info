#include <napi.h>

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <string>
#else
#include <stdbool.h>
#endif

#define PREFERENCE_KEY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Notifications\\Settings")

bool IsProcessRunning(const std::string& processName) {
    bool exists = false;

    #ifdef _WIN32
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return false;
    }
    do {
        if (std::string(pe32.szExeFile) == processName) {
            exists = true;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    #endif
    
    return exists;
}

// N-API wrapper function
Napi::Boolean IsProcessRunningWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
    Napi::String processName = info[0].As<Napi::String>();
    bool result = IsProcessRunning(processName.Utf8Value());
    return Napi::Boolean::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "isProcessRunning"), 
              Napi::Function::New(env, IsProcessRunningWrapped));
  return exports;
}

NODE_API_MODULE(processes, Init)

