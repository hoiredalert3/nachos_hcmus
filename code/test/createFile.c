#include "syscall.h"
#include "copyright.h"

int main()
{
    int len;
    /*Create a file*/
    if (CreateFile("TuiDuocTaoRaThu2.txt") == -1)
    {
        // xuất thông báo lỗi tạo tập tin

    }
    else
    {
        // xuất thông báo tạo tập tin thành công

    }
    Halt();
}