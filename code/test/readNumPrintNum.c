/* readNumPrintNum.c
 *  Simple program to test whether the ReadNum, PrintNum function works and whether the systemcall interface works.
 *	Just call ReadNum to read a number from console
 *  and use PrintNum syscall to print it back to console
 *
 */

#include "syscall.h"

int main()
{

    int a = 2;

    a = ReadNum();

    PrintNum(a);

    Halt();
    /* not reached */
}
