#include <windows.h>

void main(void) {
    SRWLOCK SRWLock;
    AcquireSRWLockExclusive(&SRWLock);
}