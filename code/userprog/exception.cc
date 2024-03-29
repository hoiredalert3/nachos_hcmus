// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#include "exception_helper.h"

#define MaxFileLength 32
#define MaxStringLength 256
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------

/*
	Increase the program counter to point the next instruction
	Copied from SC_Add
*/
void increaseProgramCounter()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(NextPCReg));

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(NextPCReg) + 4);
}

// Code copied from file
//"[2] Giao tiep giua HDH Nachos va chuong trinh nguoi dung.pdf"
//  Input: - User space address (int)
//  - Limit of buffer (int)
//  Output:- Buffer (char*)
//  Purpose: Copy buffer from User memory space to System memory space
char *User2System(int virtAddr, int limit)
{
	int i; // index
	int oneChar;
	char *kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; // need for terminal string
	if (kernelBuf == NULL)
		return kernelBuf;
	memset(kernelBuf, 0, limit + 1);
	// printf("\n Filename u2s:");
	for (i = 0; i < limit; i++)
	{
		kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		// printf("%c",kernelBuf[i]);
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

// Code copied from file
//"[2] Giao tiep giua HDH Nachos va chuong trinh nguoi dung.pdf"
// Input: - User space address (int)
// - Limit of buffer (int)
// - Buffer (char[])
// Output:- Number of bytes copied (int)
// Purpose: Copy buffer from System memory space to User memory space
int System2User(int virtAddr, int len, char *buffer)
{
	if (len < 0)
		return -1;
	if (len == 0)
		return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}

void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
		// Xử lý các exceptions được liệt kê trong machine / machine.h
		// no exception sẽ trả quyền điều khiển về HĐH
	case NoException : DEBUG(dbgSys, "No exception.\n");
		return;
		// Hầu hết các exception trong này là run - time errors
		// khi các exception này xảy ra thì user program không thể được phục hồi
		// HĐH hiển thị ra một thông báo lỗi và Halt hệ thống
	case PageFaultException : DEBUG(dbgSys, "No valid translation found.\n");
		cerr << "No valid translation found. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case ReadOnlyException:
		DEBUG(dbgSys, "Write attempted to page marked read-only.\n");
		cerr << "Write attempted to page marked read-only. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case BusErrorException:
		DEBUG(dbgSys, "Translation resulted in an invalid physical address.\n");
		cerr << "Translation resulted in an invalid physical address. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case AddressErrorException:
		DEBUG(dbgSys, "Unaligned reference or one that was beyond the end of the address space.\n");
		cerr << "Unaligned reference or one that was beyond the end of the address space. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case OverflowException:
		DEBUG(dbgSys, "Integer overflow in add or sub.\n");
		cerr << "Integer overflow in add or sub. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case IllegalInstrException:
		DEBUG(dbgSys, "Unimplemented or reserved instr.\n");
		cerr << "Unimplemented or reserved instr. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case NumExceptionTypes:
		DEBUG(dbgSys, "NumExceptionTypes.\n");
		cerr << "NumExceptionTypes. ExceptionType " << which << '\n';
		SysHalt();

		ASSERTNOTREACHED();
		break;
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;
		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			/* Modify return point */
			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		case SC_CreateFile:
			int virtAddr;
			char *filename;

			DEBUG(dbgSys, "\n SC_Create call ...");
			DEBUG(dbgSys, "\n Reading virtual address of filename");
			// Lấy tham số tên tập tin từ thanh ghi r4
			virtAddr = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "\n Reading filename.");
			// MaxFileLength là = 32
			filename = User2System(virtAddr, MaxFileLength);

			if (filename == NULL)
			{
				printf("\n Not enough memory in system");
				DEBUG(dbgSys, "\n Not enough memory in system");
				kernel->machine->WriteRegister(2, -1); // trả về lỗi cho chương
				// trình người dùng
				delete[] filename;
				return;
			}
			DEBUG(dbgSys, "\n Finish reading filename.");
			// DEBUG(‘a’,"\n File name : '"<<filename<<"'");
			//  Create file with size = 0
			//  Dùng đối tượng fileSystem của lớp OpenFile để tạo file,
			//  việc tạo file này là sử dụng các thủ tục tạo file của hệ điều
			//  hành Linux, chúng ta không quản ly trực tiếp các block trên
			//  đĩa cứng cấp phát cho file, việc quản ly các block của file
			//  trên ổ đĩa là một đồ án khác
			if (!kernel->fileSystem->Create(filename))
			{
				printf("\n Error create file '%s'", filename);
				kernel->machine->WriteRegister(2, -1);
				delete filename;
				return;
			}
			kernel->machine->WriteRegister(2, 0); // trả về cho chương trình
			// người dùng thành công
			delete[] filename;

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		case SC_ReadNum:
		{
			// Đọc số từ console vào num
			int num = ReadNumFromConsole();
			// Ghi vào thanh ghi số 2
			kernel->machine->WriteRegister(2, num);

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_PrintNum:
		{
			// Lấy tham số cần in từ thanh ghi r4
			int num = kernel->machine->ReadRegister(4);
			// In ra console
			PrintNumToConsole(num);

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_ReadChar:
		{
			//Đọc character từ console và ghi vào thanh ghi số 2
			char character = ReadCharFromConsole();
			kernel->machine->WriteRegister(2, (int)character);

			increaseProgramCounter();
			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_PrintChar:
		{
			// Lấy tham số cần in từ thanh ghi r4
			char character = (char)kernel->machine->ReadRegister(4);
			//In ra console
			PrintCharToConsole(character);

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_RandomNum:
		{
			srand(time(NULL));
			// Tạo 1 số int ngẫu nhiên và ghi vào thanh ghi số 2
			int num = GetRandomNumber();
			kernel->machine->WriteRegister(2, num);

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_ReadString:
		{
			//Đọc địa chỉ string từ thanh ghi r4
			int userString = kernel->machine->ReadRegister(4);
			//Đọc chiều dài string từ thanh ghi r5
			int len = kernel->machine->ReadRegister(5);

			if (len > MaxStringLength || len < 1)
			{
				DEBUG(dbgSys, "String length must be between 1 and " << MaxStringLength<< " (inclusive)\n");
				SysHalt();
			}
			DEBUG(dbgSys, "String length: " << len);

			char *systemString = ReadStringFromConsole(len);
			// Chuyển dữ liệu từ kernel space qua userspace
			System2User(userString, MaxStringLength, systemString);
			delete[] systemString;

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_PrintString:
		{
			//Đọc địa chỉ string từ thanh ghi r4
			int userString = kernel->machine->ReadRegister(4);

			// Chuyển dữ liệu từ userspace qua kernelspace
			char *systemString = User2System(userString, MaxStringLength);

			// In ra console
			PrintStringToConsole(systemString, MaxStringLength);
			delete[] systemString;

			increaseProgramCounter();

			return;
			ASSERTNOTREACHED();
			break;
		}

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
