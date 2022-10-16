/* readStringPrintString.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Simple program to test whether the ReadNum, PrintNum function works and whether the systemcall interface works.
 *	Just call ReadNum to read a number from console
 *  and use PrintNum syscall to print it back to console
 *
 */

#include "syscall.h"

char str[257];

int main()
{

    PrintString("Input string len: (between 1 and 256): ");
    //int a = 2;
    // a = ReadNum();

    ReadString(str, ReadNum());

    PrintString((char*)str);

    Halt();
    /* not reached */
}
