#include <windows.h>
#include <string.h>

// This pragma tells the Visual C++ linker to automatically link the User32.lib library.
#pragma comment(lib, "User32.lib")

int main() {
    // Get the handle for the standard output console.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char outputBuffer[256];
    DWORD charsWritten;

    // Define the filename and text to write.
    const char* filename = "hello_world.txt";
    const char* content = "Hello, World!";
    DWORD bytesWritten = 0;

    // 1. Create and open the file using CreateFileA.
    // This function creates a new file and returns a handle to it.
    HANDLE hFile = CreateFileA(
        filename,                  // Filename
        GENERIC_WRITE,             // Desired access (write access)
        0,                         // Share mode (do not share)
        NULL,                      // Security attributes
        CREATE_ALWAYS,             // Creation disposition (create new or overwrite existing)
        FILE_ATTRIBUTE_NORMAL,     // File attributes (normal file)
        NULL);                     // Template file handle

    if (hFile == INVALID_HANDLE_VALUE) {
        wsprintfA(outputBuffer, "Error: Could not create file. Error code: %d\n", GetLastError());
        WriteConsoleA(hConsole, outputBuffer, (DWORD)strlen(outputBuffer), &charsWritten, NULL);
        return 1;
    }

    // 2. Write the content to the file using WriteFile.
    // This function writes a specified number of bytes to the file handle.
    if (!WriteFile(
        hFile,                     // Handle to the file
        content,                   // Pointer to the data to write
        (DWORD)strlen(content),    // Number of bytes to write
        &bytesWritten,             // Pointer to a variable that receives the number of bytes written
        NULL)) {                   // Optional OVERLAPPED structure
        
        wsprintfA(outputBuffer, "Error: Could not write to file. Error code: %d\n", GetLastError());
        WriteConsoleA(hConsole, outputBuffer, (DWORD)strlen(outputBuffer), &charsWritten, NULL);
        CloseHandle(hFile);
        return 1;
    }

    // 3. Close the file handle.
    CloseHandle(hFile);

    wsprintfA(outputBuffer, "Successfully created and wrote to %s\n", filename);
    WriteConsoleA(hConsole, outputBuffer, (DWORD)strlen(outputBuffer), &charsWritten, NULL);

    // 4. Prepare to open the file with Notepad using CreateProcessA.
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command line to execute: "notepad.exe hello_world.txt"
    char command_line[MAX_PATH];
    wsprintfA(command_line, "notepad.exe %s", filename);

    // 5. Create the new process.
    if (!CreateProcessA(
        NULL,             // No module name (use command line)
        command_line,     // Command line
        NULL,             // Process handle not inheritable
        NULL,             // Thread handle not inheritable
        FALSE,            // Set handle inheritance to FALSE
        0,                // No creation flags
        NULL,             // Use parent's environment block
        NULL,             // Use parent's starting directory
        &si,              // Pointer to STARTUPINFO structure
        &pi))             // Pointer to PROCESS_INFORMATION structure
    {
        wsprintfA(outputBuffer, "CreateProcess failed (%d).\n", GetLastError());
        WriteConsoleA(hConsole, outputBuffer, (DWORD)strlen(outputBuffer), &charsWritten, NULL);
        return 1;
    }

    // Clean up process handles and exit.
    wsprintfA(outputBuffer, "Successfully launched notepad.exe to open the file.\n");
    WriteConsoleA(hConsole, outputBuffer, (DWORD)strlen(outputBuffer), &charsWritten, NULL);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
