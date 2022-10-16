/* sort.c
 *	Simple program that allows the user to input an integer array,
 *  then sort it in increasing or decreasing order.
 * 
 */

#include "syscall.h"
#define MAXSIZE 100

void inputArray(int *arr, int n);

void swap(int *a, int *b);

void bubbleSort(int *arr, int n, int sortOrder);

void printArray(int *arr, int n);

int main()
{
    int n = -1;
    int arr[MAXSIZE];
    int sortOrder = 0;

    while (n < 0 || n > 100)
    {
        PrintString("Enter the number of elements of the array (between 0 and 100 (inclusive)): ");
        n = ReadNum();

        if (n < 0 || n > 100)
        {
            PrintString("The number of elements of the array must be between 0 and 100 (inclusive)!\n");
            PrintString("Please input again!\n");
        }
    }

    inputArray(arr, n);

    PrintString("Enter the order that the array will be sorted in (0: increasing, otherwise: decreasing):\n");
    sortOrder = ReadNum();
    if (sortOrder == 0)
        PrintString("You chose increasing order\n");
    else
        PrintString("You chose decreasing order\n");

    PrintString("The original array:\n");
    printArray(arr, n);

    bubbleSort(arr, n, sortOrder);

    PrintString("The sorted array:\n");
    printArray(arr, n);

    Halt();
    /* not reached */
}

void inputArray(int *arr, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        PrintString("Enter element number ");
        PrintNum(i);
        PrintString(": ");
        arr[i] = ReadNum();
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int *arr, int n, int sortOrder)
{
    int i, j;
    int swapped;

    for (i = 0; i < n - 1; ++i)
    {
        swapped = 0;
        for (j = 0; j < n - i - 1; ++j)
        {
            if (sortOrder == 0)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(&arr[j], &arr[j + 1]);
                    swapped = 1;
                }
            }
            else 
                if (arr[j] < arr[j + 1])
                {
                    swap(&arr[j], &arr[j + 1]);
                    swapped = 1;
                }
        }

        // If no swap happen, break the loop
        if (swapped == 0)
            break;
    }
}

void printArray(int *arr, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        PrintNum(arr[i]);
        PrintChar(' ');
    }
    PrintChar('\n');
}