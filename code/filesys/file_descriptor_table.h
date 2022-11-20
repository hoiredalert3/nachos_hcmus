/*
*************************************************************
*
* filesys/file_descriptor_table.h
*
* Provide class file descriptor table for filesys.h
*
* by Ngo Phuc Hoi
*
*************************************************************
*/

#ifndef FILE_DESCRIPTOR_TABLE
#define FILE_DESCRIPTOR_TABLE
#include "sysdep.h"
#include "openfile.h"
#include "syscall.h"

#define MAX_FILE 20

#define CONSOLE_INPUT 0
#define CONSOLE_OUTPUT 1

#define READWRITE 0
#define READ 1
#define WRITE 2

class FileDescriptorTable
{
private:
    OpenFile **openFile;
    int *fileOpenMode;

public:
    FileDescriptorTable()
    {
        openFile = new OpenFile *[MAX_FILE];
        fileOpenMode = new int[MAX_FILE];
        fileOpenMode[CONSOLE_INPUT] = READ;
        fileOpenMode[CONSOLE_OUTPUT] = WRITE;
    }

    int Insert(char *fileName, int openMode)
    {
        int freeIndex = -1;
        int fileDescriptor = -1;
        for (int i = 2; i < MAX_FILE; i++)
        {
            if (openFile[i] == NULL)
            {
                freeIndex = i;
                break;
            }
        }

        if (freeIndex == -1)
        {
            return -1;
        }

        if (openMode == READWRITE)
            fileDescriptor = OpenForReadWrite(fileName, FALSE);
        if (openMode == READ)
            fileDescriptor = OpenForRead(fileName, FALSE);

        if (fileDescriptor == -1)
            return -1;
        openFile[freeIndex] = new OpenFile(fileDescriptor);
        fileOpenMode[freeIndex] = openMode;

        return freeIndex;
    }

    int Remove(int index)
    {
        if (index < 2 || index >= MAX_FILE)
            return -1;
        if (openFile[index])
        {
            delete openFile[index];
            openFile[index] = NULL;
            return 0;
        }
        return -1;
    }

    int Read(char *buffer, int charCount, int index)
    {
        if (index >= MAX_FILE)
            return -1;
        if (openFile[index] == NULL)
            return -1;

        int result = openFile[index]->Read(buffer, charCount);
        return result;
    }

    int Write(char *buffer, int charCount, int index)
    {
        if (index >= MAX_FILE)
            return -1;
        if (openFile[index] == NULL || fileOpenMode[index] == READ)
            return -1;
        int result = openFile[index]->Write(buffer, charCount);
        return result;
    }

    int Seek(int pos, int index)
    {
        if (index <= 1 || index >= MAX_FILE)
            return -1;
        if (openFile[index] == NULL)
            return -1;
        // use seek(-1) to move to the end of file
        if (pos == -1)
            pos = openFile[index]->Length();
        if (pos < 0 || pos > openFile[index]->Length())
            return -1;
        return openFile[index]->Seek(pos);
    }

    ~FileDescriptorTable()
    {
        for (int i = 0; i < MAX_FILE; i++)
        {
            if (openFile[i])
                delete openFile[i];
        }
        delete[] openFile;
        delete[] fileOpenMode;
    }
};

#endif /* FILE_DESCRIPTOR_TABLE */
