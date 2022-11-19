/* readFile.c
 *	Simple program to test Read syscall and whether the systemcall interface works.
 *
 *	Just call Read(buffer, size, id) to read content of a file
 *      size: number of bytes
 *      id: OpenFileId
 */

#include "syscall.h"

char s[124];

int main()
{
    // Mo file hello2.txt
    OpenFileId id1, id2;
    int num;
    char ch;

    id1 = Open("hello2.txt", 1);
    PrintNum(id1);
    PrintChar('\n');

    Read(s, 5, 2);
    PrintString(s);

    id2 = Open("hello1.txt", 0);

    num = RandomNum() % 10;
    ch = num + '0';
    PrintNum(num);
    PrintChar('\n');
    Write(&ch, 1, id2);

    Seek(-1, id2);
    Write(&ch, 1, id2);

    Halt();
    /* not reached */
}
