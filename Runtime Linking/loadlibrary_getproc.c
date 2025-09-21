#include <windows.h>

typedef int (WINAPI *MessageBoxA_t)(HWND, LPCSTR, LPCSTR, UINT);

int main() {
    // Load user32.dll
    HMODULE hUser32 = LoadLibraryA("user32.dll");
    if (hUser32 == NULL) {
        return 1; // Failed to load library
    }

    // Get address of MessageBoxA
    MessageBoxA_t pMessageBoxA = (MessageBoxA_t)GetProcAddress(hUser32, "MessageBoxA");
    if (pMessageBoxA == NULL) {
        FreeLibrary(hUser32);
        return 1; // Failed to get function address
    }

    // Call MessageBoxA
    pMessageBoxA(NULL, "Hello, World!", "Loaded at Runtime :)", MB_OK | MB_ICONINFORMATION);

    // Clean up
    FreeLibrary(hUser32);
    return 0;
}