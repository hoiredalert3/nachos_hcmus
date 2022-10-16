/* ascii.c
 *	Simple program to print all printable character of the ASCII table
 *
 */

#include "syscall.h"

int main()
{
    int i;
    int start = 32, end = 126;

    for (i = start; i <= end; ++i)
    {
        PrintNum(i);
        PrintChar(' ');
        PrintChar(i);
        PrintChar('\n');
    }
    
    Halt();
    /* not reached */
}