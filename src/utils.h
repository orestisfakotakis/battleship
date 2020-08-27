#ifndef UTILS_H
#define UTILS_H

// Define Sleep in non-Windows system as it is on windows
#ifdef _WIN32
#   include <windows.h>
#   include <conio.h>
#else
#   include <signal.h>
#   include <unistd.h>
#   define Sleep(x) usleep((x)*1000)
    int getch();
#endif

int getAsyncKey(void);
void clrscrn();

#endif // UTILS_H
