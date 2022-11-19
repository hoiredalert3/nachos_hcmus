/* removeFile.c
 *	Simple program to test Remove syscall and whether the systemcall interface works.
 *
 *	Just call Remove(name) to open a file
 *  
 */

#include "syscall.h"

int main()
{
    //Xoa file hello.txt
    //In ra 0 neu thanh cong, in ra -1 neu that bai
    PrintNum(Remove("hello.txt"));

    Halt();
    /* not reached */
}
