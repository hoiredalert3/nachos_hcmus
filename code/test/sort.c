/* sort.c
 *	Simple program that allows the user to input an integer array,
 *  then sort it in increasing or decreasing order.
 * 
 */

#include "syscall.h"
#define MAXSIZE 100

// Let the user input an integer array of size int
void inputArray(int *arr, int n);

// Swap two integers
void swap(int *a, int *b);

// bubbleSort function to sort an integer array in increasing or decreasing order
// sortOrder = 0: increasing, otherwise: decreasing
void bubbleSort(int *arr, int n, int sortOrder);

// Function to print an integer array
void printArray(int *arr, int n);

int main()
{
    //n - size of the array
    int n = -1;
    int arr[MAXSIZE];
    // sortOrder = 0: increasing, otherwise: decreasing
    int sortOrder = 0;

    //Input n - size of the array (0 <= n <= 100)
    while (n < 0 || n > 100)
    {
        PrintString("Enter the number of elements of the array (between 0 and 100 (inclusive)): ");
        n = ReadNum();
        //Check and ask the user to input n again
        if (n < 0 || n > 100)
        {
            PrintString("The number of elements of the array must be between 0 and 100 (inclusive)!\n");
            PrintString("Please input again!\n");
        }
    }
    // Let the user input the array with size n
    inputArray(arr, n);

    //Let the user input the sorting order
    PrintString("Enter the order that the array will be sorted in (0: increasing, otherwise: decreasing):\n");
    sortOrder = ReadNum();
    if (sortOrder == 0)
        PrintString("You chose increasing order\n");
    else
        PrintString("You chose decreasing order\n");

    //Print the original array
    PrintString("The original array:\n");
    printArray(arr, n);

    //Sort the array using bubbleSort algorithm
    bubbleSort(arr, n, sortOrder);

    // Print the original array
    PrintString("The sorted array:\n");
    printArray(arr, n);

    Halt();
    /* not reached */
}

//Let the user input an integer array of size int
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

//Swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// bubbleSort function to sort an integer array in increasing or decreasing order
// sortOrder = 0: increasing, otherwise: decreasing
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

//Function to print an integer array
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