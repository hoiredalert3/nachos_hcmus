/* readCharPrintChar.c
 *	Simple program to test whether the RandomNum function works and whether the systemcall interface works.
 *
 *	Just call RandomNum to get a random integer
 *  and use PrintNum to print it to console
 *
 */

#include "syscall.h"

int main()
{
    int num = RandomNum();

    PrintNum(num);

    Halt();
    /* not reached */
}
