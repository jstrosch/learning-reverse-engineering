# Learning Reverse Engineering

This repository contains several programs designed to help you in learning reverse engineering and malware anlaysis. The type of program is organized by concept it is focused, you can see this through the root folder structure. Source code along with compiled binaries are provided in each directory.

I discuss many of these programs through online videos and courses and you may find the following helpful:

- Getting Started with x86 Assembly - [YouTube Playlist](https://www.youtube.com/playlist?list=PLHJns8WZXCdvESvdr1BRjo4RHiR1Ylhw9)

- Getting Started with Reverse Engineering - [YouTube Playlist](https://www.youtube.com/playlist?list=PLHJns8WZXCdvaD7-xR7e5FJNW_6H9w-wC) and full courses on [Pluralsight](https://www.pluralsight.com/courses/reverse-engineering-getting-started)

- Analyzing C++ objects in Ghidra - [YouTube playlist](https://www.youtube.com/playlist?list=PLHJns8WZXCdu6kPwPpBhA0mfdB4ZuWy6M)

- Analyzing C Structures in IDA Pro - [YouTube playlist](https://www.youtube.com/playlist?list=PLHJns8WZXCdu7zDObGl7oEO0APWOEnDNT)

- Essential Elements of the Portable Executable (PE) file - [YouTube playlist](https://www.youtube.com/playlist?list=PLHJns8WZXCdstHnLaxcz-CO74fO4Q88_8)

## Other Tools You May Find Helpful

- [sclauncher](https://github.com/jstrosch/sclauncher): A shellcode launcher and debugging tool

## Compiling the Source Code

These programs are intended to be compiled with the C/C++ compiler from Microsoft. You can use the `Developer Command Prompt` after installing the free/community version to compile using `cl`. An example of this command would be:

```cl <path/to/source_code>```

This should produce two files: `.obj` and `.exe` using the name of the input file. You can typically ignore the `.obj` file, the `.exe` is what you will analyze. Please note, occassionally specific compiler flags are used to obtain desired affects in the resulting binary. These compiler flags will be identified in the related videos or noted in the README in the specific folder.