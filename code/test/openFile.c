/* openFile.c
 *	Simple program to test OpenFile syscall and whether the systemcall interface works.
 *
 *	Just call OpenFile(name, mode) to open a file
 *  mode:
 *      0 - read and write mode
 *      1 - read-only mode
 */

#include "syscall.h"

int main()
{
    // Mo thu file hello.txt, in ra 2 vi day la file dau tien duoc mo
    // Console input la 0, Console output la 1
    PrintNum(Open("hello.txt", 0));
    PrintChar('\n');

    //Dong file hello.txt
    PrintNum(Close(2));
    PrintChar('\n');

    //Mo lai file hello.txt
    PrintNum(Open("hello.txt", 0));
    PrintChar('\n');

    // Mo thu file hello.txt, in ra 3 vi day la file thu 2 duoc mo
    PrintNum(Open("hello2.txt", 0));

    Halt();
    /* not reached */
}
