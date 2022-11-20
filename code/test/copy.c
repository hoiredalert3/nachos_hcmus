/* cat.c
 *	Simple program to copy content of a source file to an output file
 *
 */

#include "syscall.h"

int main()
{
    OpenFileId sourceId, outputId;
    int bytesRead;
    char sourceName[50];
    char outputName[50];
    char buffer[256];

    PrintString("Nhap ten file nguon: ");
    Read(sourceName, 50, ConsoleInput_);

    PrintString("Nhap ten file dich: ");
    Read(outputName, 50, ConsoleInput_);

    sourceId = Open(sourceName, 1);
    if (sourceId == -1)
    {
        PrintString("Mo file nguon ");
        PrintString(sourceName);
        PrintString(" that bai\n ");
    }
    else
    {
        PrintString("Mo file nguon ");
        PrintString(sourceName);
        PrintString(" thanh cong\n ");

        if (Create(outputName) == -1)
        {
            PrintString("Tao file ");
            PrintString(outputName);
            PrintString(" that bai\n ");
        }
        else
        {
            PrintString("Tao file ");
            PrintString(outputName);
            PrintString(" thanh cong\n ");

            outputId = Open(outputName, 0);
            while (1)
            {
                bytesRead = Read(buffer, 255, sourceId);
                if (bytesRead <= 0)
                    break;
                Write(buffer, bytesRead, outputId);
            }
            Close(outputId);
            Write("Copy file thanh cong\n", 20, ConsoleOutput_);
        }

        PrintChar('\n');
        Close(sourceId);
    }

    Halt();
    /* not reached */
}