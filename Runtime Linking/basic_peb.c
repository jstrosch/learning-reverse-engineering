#include <windows.h>
#include <stdio.h>

/*

TEB
 |
 +----------------> PEB
 |                    |
 |                    +--> Ldr --> PEB_LDR_DATA
 |                                   |
 |                                   +--> InMemoryOrderModuleList (LIST_ENTRY)
 |                                         |
 |                                         +--> LDR_DATA_TABLE_ENTRY (1st DLL)
 |                                         |      |
 |                                         |      +--> BaseDllName --> UNICODE_STRING --> "kernel32.dll"
 |                                         |      +--> DllBase --> 0x7FFE0000
 |                                         |
 |                                         +--> LDR_DATA_TABLE_ENTRY (2nd DLL)
 |                                         |      |
 |                                         |      +--> BaseDllName --> UNICODE_STRING --> "ntdll.dll"
 |                                         |      +--> DllBase --> 0x7FFF0000
 |                                         |
 |                                         +--> ... (other DLLs)
 |
 +----------------> (Other TEB fields)

*/

// Define UNICODE_STRING structure
typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

// Define structures for PEB and LDR data
typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN SpareBool;
    HANDLE Mutant;
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
} PEB, *PPEB;

int main() {
    // Get the PEB address from the TEB
    PPEB peb;
#if defined(_M_X64) // x64
    peb = (PPEB)__readgsqword(0x60);
#else // x86
    peb = (PPEB)__readfsdword(0x30);
#endif

    // Get the LDR data from the PEB
    PPEB_LDR_DATA ldr = peb->Ldr;
    PLIST_ENTRY moduleListHead = &ldr->InMemoryOrderModuleList;
    PLIST_ENTRY moduleListEntry = moduleListHead->Flink;

    // Iterate through the module list
    while (moduleListEntry != moduleListHead) {
        // Get the LDR entry
        PLDR_DATA_TABLE_ENTRY ldrEntry = CONTAINING_RECORD(moduleListEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

        // Get the DLL name (UNICODE_STRING)
        PUNICODE_STRING dllName = &ldrEntry->BaseDllName;
        if (dllName->Buffer) {
            // Convert Unicode string to ANSI for printing
            char dllNameAnsi[256] = {0};
            WideCharToMultiByte(CP_ACP, 0, dllName->Buffer, dllName->Length / sizeof(WCHAR), dllNameAnsi, sizeof(dllNameAnsi), NULL, FALSE);

            // Check if the module is kernel32.dll
            if (_stricmp(dllNameAnsi, "kernel32.dll") == 0) {
                printf("Found kernel32.dll in memory:\n");
                printf("  Name: %s\n", dllNameAnsi);
                printf("  Base Address: %p\n", ldrEntry->DllBase); // Fixed format string issue
                break; // Exit after finding kernel32.dll
            }
        }

        // Move to the next module
        moduleListEntry = moduleListEntry->Flink;
    }

    return 0;
}