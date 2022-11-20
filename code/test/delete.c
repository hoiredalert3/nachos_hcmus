/* delete.c
 *	Simple program to test Remove syscall and whether the systemcall interface works.
 *
 *	Just call Remove(name) to remove a file
 *
 */

#include "syscall.h"

int main()
{
    int result;
    char filename[256];
    // Yeu cau nguoi dung nhap ten file can xoa
    PrintString("Nhap ten file can xoa: ");
    ReadString(filename, 255);

    // Xoa file
    result = Remove(filename);

    // In result = 0 neu thanh cong, result = -1 neu that bai
    if (result == 0)
    {
        PrintString("Xoa file ");
        PrintString(filename);
        PrintString(" thanh cong\n");
    }

    Halt();
    /* not reached */
}
