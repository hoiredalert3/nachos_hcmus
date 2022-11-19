/* create.c
 *	Simple program to test system call int Create(char *name)
 *  Create an empty file
 *
 */

#include "syscall.h"

char filename[32];

int main()
{
    ReadString(filename, 32);

    PrintString(filename);

    if (Create(filename) == -1)
    {
        PrintString("Tao file ");
        PrintString(filename);
        PrintString(" that bai\n ");
    }
    else
    {
        PrintString("Tao file ");
        PrintString(filename);
        PrintString(" thanh cong\n ");
    }

    Halt();
    /* not reached */
}