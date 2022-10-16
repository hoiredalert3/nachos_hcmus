/* readCharPrintChar.c
 *	Simple program to test whether the ReadChar, PrintChar function works and whether the systemcall interface works.
 *
 *	Just call ReadNum to read a number from console
 *  and use PrintNum syscall to print it back to console
 *
 */

#include "syscall.h"

int main()
{
    char ch;

    ch = ReadChar();

    PrintChar(ch);

    Halt();
    /* not reached */
}
