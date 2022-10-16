/**************************************************************
 *
 * userprog/exception_helper.h
 *
 * Support functions for exception.cc
 *
 * by Ngo Phuc Hoi
 *
 **************************************************************/

#ifndef __USERPROG_EXCEPTION_HELPER_H__
#define __USERPROG_EXCEPTION_HELPER_H__

#include "kernel.h"
#include "synchconsole.h"
#include <stdlib.h>
#include <stdint.h>

#define MAX_NUM_LENGTH 11
//-2147483648 <= int32 <=2147483647
// so the maximum length of an int32 string is 11
// A character buffer to read and write int32 number
char characterBuffer[MAX_NUM_LENGTH + 1];

//Check if a character is empty space
char isEmptySpace(char ch) 
{
    return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\x0b');
}

/**
 * Read characters from console and store them in characterBuffer
 * Stops when meeting an empty space character:
 *  '\n' Line Feed
 *  '\r' Carriage Return
 *  '\t' Horizontal Tab
 *  ' ' Space
 *  '\x0b' 	Vertical Tab
 *  EOF
 **/
void readCharacters()
{
    memset(characterBuffer, 0, sizeof(characterBuffer));
    char ch = kernel->synchConsoleIn->GetChar();

    if (ch == EOF || isEmptySpace(ch))
    {
        DEBUG(dbgSys, "Illegal character found, ascii code " << (int)ch << '\n');
        return;
    }

    int len = 0;

    while (!(isEmptySpace(ch) || ch == EOF))
    {
        characterBuffer[len++] = ch;
        if (len > MAX_NUM_LENGTH)
        {
            DEBUG(dbgSys, "The number is to long to fit in int32");
            return;
        }
        ch = kernel->synchConsoleIn->GetChar();
    }
}

int ReadNumFromConsole()
{
    readCharacters();

    int len = strlen(characterBuffer);
    // Return 0 if kernel didn't read any character
    if (len == 0)
        return 0;

    // 2147483648 doesn't fit in int32 so we can't store it in an int32 integer
    // Therefore, the string "-2147483648" must be compare manually
    if (strcmp(characterBuffer, "-2147483648") == 0)
        return INT32_MIN;

    bool negative = characterBuffer[0] == '-';

    int num = 0;

    for (int i = negative; i < len; ++i)
    {
        
        char c = characterBuffer[i];

        if (c < '0' || c > '9')
        {
            DEBUG(dbgSys, "Illegal character found " << characterBuffer << ", number expected");
            return 0;
        }
        num = num * 10 + (c - '0');
    }

    if (negative)
        num = -num;

    //If negative is true but num is positive
    //or if negative is false but num is negative
    //then integer overflow happened
    if ((negative && num > 0) || (!negative && num < 0))
    {
        DEBUG(dbgSys, "Number " << characterBuffer << " doesn't fit in int32");
        return 0;
    }
        
    // Num is safe to return
    return num;

}

void PrintNumToConsole(int num)
{
    //Print out '0' if num is 0
    if (num == 0)
        return kernel->synchConsoleOut->PutChar('0');

    // Because 2147483648 doesn't fit in int32, we must print -2147483648 (INT32_MIN) manually
    if (num == INT32_MIN)
    {
        kernel->synchConsoleOut->PutChar('-');
        for (int i = 0; i < 10; ++i)
            kernel->synchConsoleOut->PutChar("2147483648"[i]);
        return;
    }
    //If num < 0, print '-' and reverse the sign of num
    if (num < 0)
    {
        kernel->synchConsoleOut->PutChar('-');
        num = -num;
    }

    int n = 0;
    // Store num's digits in characterBuffer
    while (num)
    {
        characterBuffer[n++] = num % 10;
        num /= 10;
    }
    //Print to console
    for (int i = n - 1; i >= 0; --i)
        kernel->synchConsoleOut->PutChar(characterBuffer[i] + '0');
}

char ReadCharFromConsole()
{
    return kernel->synchConsoleIn->GetChar();
}

void PrintCharToConsole(char ch)
{
    kernel->synchConsoleOut->PutChar(ch);
}

int GetRandomNumber()
{
    int num = rand();
    // GetRandomNumber must return a positive integer
    if (num == 0)
        ++num;
    return num;
}

char *ReadStringFromConsole(int len)
{
    char *str;
    str = new char[len + 1];
    for (int i = 0; i < len; ++i)
    {
        str[i] = kernel->synchConsoleIn->GetChar();
    }
    str[len] = '\0';
    return str;
}

void PrintStringToConsole(char* str, int maxLen)
{
    int i = 0;
    while (str[i] != '\0' && i < maxLen)
    {
        kernel->synchConsoleOut->PutChar(str[i]);
        ++i;
    }
}

int stringLen(int strAddr, int limit)
{
    int length = 0;
    int oneChar;

    do
    {
        kernel->machine->ReadMem(strAddr + length, 1, &oneChar);
        length++;
    } while (oneChar == '\0' || length > limit);

    return length;
}

#endif /* ! __USERPROG_EXCEPTION_HELPER_H__ */
