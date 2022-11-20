/* concatenate.c
 *	Simple program to concatenate the contents of 2 files
 *  Requires entering the name of source file 1 and source file 2
 *  Concatenate the content of source file 2 to the end of source file 1
 */

#include "syscall.h"

int main()
{
    OpenFileId source2Id, source1Id;
    int bytesRead;
    char source2Name[50];
    char source1Name[50];
    char buffer[256];

    PrintString("Chuong trinh noi file nguon 1 vao cuoi file nguon 2\n");
    PrintString("Nhap ten file nguon 1: ");
    Read(source2Name, 50, ConsoleInput_);

    PrintString("Nhap ten file nguon 2: ");
    Read(source1Name, 50, ConsoleInput_);

    source2Id = Open(source2Name, 1);
    if (source2Id == -1)
    {
        PrintString("Mo file nguon 2 ");
        PrintString(source2Name);
        PrintString(" that bai\n ");
    }
    else
    {
        PrintString("Mo file nguon 2 ");
        PrintString(source2Name);
        PrintString(" thanh cong\n ");

        source1Id = Open(source1Name, 0);
        Seek(-1, source1Id);
        while (1)
        {
            bytesRead = Read(buffer, 255, source2Id);
            if (bytesRead <= 0)
                break;
            Write(buffer, bytesRead, source1Id);
        }
        Close(source1Id);
        Write("Noi 2 file thanh cong\n", 20, ConsoleOutput_);

        PrintChar('\n');
        Close(source2Id);
    }

    Halt();
    /* not reached */
}