/* help.c
 *	Simple program help to print out basic information of the group
 *  and a brief description of the sort and ascii programs.
 *	
 *	Just call PrintString to print out many lines of text to the consle
 */

#include "syscall.h"

int main()
{

    PrintString("Group name: HCMUS_K20_TN\n");
    PrintString("Group members:\n");
    PrintString("\t20120070 - Huynh Thiet Gia\n");
    PrintString("\t20120291 - Ngo Phuc Hoi\n");

    PrintString("Brief description of the sort and ascii programs:\n\n");

    PrintString("ascii: A program to print all printable character of the ASCII table\n");
    PrintString("Source file: ascii.c\n");
    PrintString("How to build:\n");
    PrintString(" - Open terminal at directory code/test and run 'make' or 'make ascii'\n");
    PrintString("How to run:\n");
    PrintString(" - Open terminal at directory code/test and run ../build.linux/nachos -x ascii\n\n");

    PrintString("sort: A program that allows the user to input an integer array, then sort it in increasing or decreasing order\n");
    PrintString("The sort program uses the bubble sort algorithm\n");
    PrintString("Source file: sort.c\n");
    PrintString("How to build:\n");
    PrintString(" - Open terminal at directory code/test and run 'make' or 'make sort'\n");
    PrintString("How to run:\n");
    PrintString("Open terminal at directory code / test, run../ build.linux / nachos - x sort to start the sort program\n ");
    PrintString(" - Input the length of the array (0 <= length <= 100)\n");
    PrintString(" - Input n elements of the array\n");
    PrintString(" - Enter the order that the array will be sorted in (0: increasing, otherwise: decreasing)\n");
    PrintString(" - The program will print the original array and then print the sorted array\n");
    PrintString(" - Finally the program will exit\n");

    Halt();
    /* not reached */
}
