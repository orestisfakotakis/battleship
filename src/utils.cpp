#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef _WIN32
#   include <conio.h>
#else
#   include <termios.h>
#   include <unistd.h>
#   include <sys/ioctl.h>
#   include <sys/fcntl.h>
#endif

/* UI Functions */

#ifdef _WIN32

void clrscrn()
{
    system("cls");
}

int getAsyncKey()
{
    if (kbhit())
        return getch();
    else
        return 0;
}

#else

void clrscrn()
{
    write(1,"\E[H\E[2J",7);
}

int getch()
{
    return getchar();
}

int getAsyncKey(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    // ungetc(ch, stdin);
    return ch;
  }

  return 0;
}

#endif
