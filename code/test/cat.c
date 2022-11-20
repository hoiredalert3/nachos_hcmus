/* cat.c
 *	Simple program to display the content of a file
 *
 */

#include "syscall.h"

int main()
{
    OpenFileId id1;
    int fileLen;
    int bytesRead;
    char filename[50];
    char buffer[256];

    PrintString("Nhap ten file can hien thi noi dung: ");
    Read(filename, 50, ConsoleInput_);
    // ReadString(filename, 50);

    id1 = Open(filename, 1);
    if (id1 == -1)
    {
        PrintString("Mo file ");
        PrintString(filename);
        PrintString(" that bai\n ");
    }
    else
    {
        PrintString("Mo file ");
        PrintString(filename);
        PrintString(" thanh cong\n ");

        PrintString("Noi dung file ");
        PrintString(filename);
        PrintString(" la:\n");

        while (1)
        {
            bytesRead = Read(buffer, 255, id1);

            if (bytesRead <= 0)
                break;
            Write(buffer, bytesRead, ConsoleOutput_);
        }
        PrintChar('\n');
        Close(id1);
    }

    Halt();
    /* not reached */
}