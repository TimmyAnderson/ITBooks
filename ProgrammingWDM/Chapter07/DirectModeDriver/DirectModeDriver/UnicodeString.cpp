//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
#include <ntstrsafe.h>
#include "UnicodeString.h"
#include "Defines.h"
//-------------------------------------------------------------------------------------------------------
CUnicodeString::CUnicodeString(void)
{
	Init();
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::CUnicodeString(const char* AnsiString)
{
	Init();

	NTSTATUS													Status;
	ANSI_STRING													String;

	RtlInitAnsiString(&String,AnsiString);

	// Returns LENGTH WITH NULL CHAR.
	ULONG														StringLengthInBytesWithNULL=RtlAnsiStringToUnicodeSize(&String);

	if (StringLengthInBytesWithNULL<=MAXUSHORT)
	{
		USHORT													LengthInBytes=USHORT(StringLengthInBytesWithNULL-CHAR_SIZE);
		USHORT													LengthInChars=LengthInBytes/CHAR_SIZE;
		USHORT													MaximumLengthInBytes=USHORT(StringLengthInBytesWithNULL);
		PWSTR													Buffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,MaximumLengthInBytes,STRING_TAG);

		if (Buffer!=NULL)
		{
			// Initializes MString.Buffer and MString.MaximumLength. MString.MaximumLength must contain BUFFER SIZE in BYTES.
			RtlInitEmptyUnicodeString(&MString,Buffer,MaximumLengthInBytes);

			if (NT_SUCCESS(Status=RtlAnsiStringToUnicodeString(&MString,&String,FALSE))==FALSE)
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION RtlAnsiStringToUnicodeString() FAILED with STATUS [%X] !\n",Status);
				SetError();
			}

			MString.Buffer[LengthInChars]=NULL_CHAR;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
			SetError();
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): Length [%d] is GREATER than MAXUSHORT [%d] !\n",StringLengthInBytesWithNULL,MAXUSHORT);
		SetError();
	}
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::CUnicodeString(PCWSTR String)
{
	Init();
	
	NTSTATUS													Status;
	size_t														MaxAllowedLengthInBytes=NTSTRSAFE_UNICODE_STRING_MAX_CCH*CHAR_SIZE;
	size_t														StringLengthInBytesWithoutNULL;

	// Returns LENGTH WITHOUT NULL CHAR.
	if (NT_SUCCESS(Status=RtlStringCbLengthW(String,MaxAllowedLengthInBytes,&StringLengthInBytesWithoutNULL))!=FALSE)
	{
		USHORT													LengthInBytes=USHORT(StringLengthInBytesWithoutNULL);
		USHORT													LengthInChars=LengthInBytes/CHAR_SIZE;
		USHORT													MaximumLengthInBytes=LengthInBytes+CHAR_SIZE;
		PWSTR													Buffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,MaximumLengthInBytes,STRING_TAG);

		if (Buffer!=NULL)
		{
			// Initializes MString.Buffer and MString.MaximumLength. MString.MaximumLength must contain BUFFER SIZE in BYTES.
			RtlInitEmptyUnicodeString(&MString,Buffer,MaximumLengthInBytes);
			RtlCopyMemory(MString.Buffer,String,LengthInBytes);
			MString.Length=LengthInBytes;
			MString.Buffer[LengthInChars]=NULL_CHAR;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
			SetError();
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION RtlStringCbLengthW() FAILED with STATUS [%X] !\n",Status);
		SetError();
	}
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::CUnicodeString(ULONG Value)
{
	Init();

	NTSTATUS													Status;
	USHORT														LengthInBytes=32;
	USHORT														LengthInChars=32/CHAR_SIZE;
	USHORT														MaximumLengthInBytes=LengthInBytes+CHAR_SIZE;
	PWSTR														Buffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,MaximumLengthInBytes,STRING_TAG);

	if (Buffer!=NULL)
	{
		RtlInitEmptyUnicodeString(&MString,Buffer,MaximumLengthInBytes);

		if (NT_SUCCESS(Status=RtlIntegerToUnicodeString(Value,0,&MString))==FALSE)
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION RtlIntegerToUnicodeString() FAILED with STATUS [%X] !\n",Status);
			SetError();
		}

		MString.Buffer[LengthInChars]=NULL_CHAR;
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
		SetError();
	}
}
//-------------------------------------------------------------------------------------------------------
// Original string has ERROR FLAG set, set ERROR FLAG on current OBJECT.
CUnicodeString::CUnicodeString(const CUnicodeString& Original)
{
	Init();

	if (Original.MErrorFlag==false)
	{
		PWSTR													NewBuffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,Original.MString.MaximumLength,STRING_TAG);
		USHORT													LengthInBytes=USHORT(Original.MString.MaximumLength-CHAR_SIZE);
		USHORT													LengthInChars=LengthInBytes/CHAR_SIZE;
		
		if (NewBuffer!=NULL)
		{
			RtlInitEmptyUnicodeString(&MString,NewBuffer,Original.MString.MaximumLength);
			RtlCopyUnicodeString(&MString,&Original.MString);
			MString.Buffer[LengthInChars]=NULL_CHAR;
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
			SetError();
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): COPY CONSTRUCTOR FAILED because STRING has ERROR FLAG set !\n");
		SetError();
	}
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::~CUnicodeString(void)
{
	Reset();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void* CUnicodeString::operator new(size_t Size)
{
	PVOID														Object=ExAllocatePoolWithTag(NonPagedPool,Size,STRING_TAG);

	if (Object==NULL)
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
	}

	return(Object);
}
//-------------------------------------------------------------------------------------------------------
void CUnicodeString::operator delete(void* Pointer)
{
	if (Pointer==NULL)
	{
		return;
	}

	ExFreePoolWithTag(Pointer,STRING_TAG);
}
//-------------------------------------------------------------------------------------------------------
// If any of two OPERANDS has ERROR FLAG set, FUNCTION returns FALSE.
// Comparison is CASE SENSITIVE.
bool CUnicodeString::operator==(const CUnicodeString& Operand) const
{
	if (MErrorFlag==false && Operand.MErrorFlag==false)
	{
		BOOLEAN													Result=RtlEqualUnicodeString(&MString,&Operand.MString,FALSE);

		if (Result!=FALSE)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): OPERATOR== FAILED because STRING (%d,%d) has ERROR FLAG set !\n",MErrorFlag,Operand.MErrorFlag);
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
// If any of two OPERANDS has ERROR FLAG set, set ERROR FLAG on current OBJECT.
CUnicodeString CUnicodeString::operator=(const CUnicodeString& Operand)
{
	if (MErrorFlag==false && Operand.MErrorFlag==false)
	{
		if (&Operand!=this)
		{
			if (Operand.MString.Length>=MString.Length)
			{
				USHORT											MaximumLength=Operand.MString.MaximumLength;

				// FIELD MString.MaximumLength ALWAYS counting NULL_CHAR.
				PWSTR											NewBuffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,MaximumLength,STRING_TAG);

				if (NewBuffer!=NULL)
				{
					Reset();
					RtlInitEmptyUnicodeString(&MString,NewBuffer,MaximumLength);

					RtlCopyUnicodeString(&MString,(PUNICODE_STRING) &Operand.MString);
					MString.Buffer[LengthInChars(false)]=NULL_CHAR;

					return(*this);
				}
				else
				{
					DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
					SetError();

					return(*this);
				}
			}
			else
			{
				RtlCopyUnicodeString(&MString,(PUNICODE_STRING) &Operand.MString);
				MString.Buffer[LengthInChars(false)]=NULL_CHAR;

				return(*this);
			}
		}
		else
		{
			return(*this);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): OPERATOR= FAILED because STRING (%d,%d) has ERROR FLAG set !\n",MErrorFlag,Operand.MErrorFlag);
		SetError();

		return(*this);
	}
}
//-------------------------------------------------------------------------------------------------------
// If any of two OPERANDS has ERROR FLAG set, set ERROR FLAG to newly created OBJECT.
CUnicodeString CUnicodeString::operator+(const CUnicodeString& Operand) const
{
	NTSTATUS													Status;
	CUnicodeString												NewString;

	if (MErrorFlag==false && Operand.MErrorFlag==false)
	{
		USHORT													LengthInBytes=MString.Length+Operand.MString.Length;
		USHORT													LengthInChars=LengthInBytes/CHAR_SIZE;
		USHORT													MaxLengthInBytes=LengthInBytes+CHAR_SIZE;
		PWSTR													NewBuffer=(PWSTR) ExAllocatePoolWithTag(NonPagedPool,MaxLengthInBytes,STRING_TAG);

		if (NewBuffer!=NULL)
		{
			RtlInitEmptyUnicodeString(&NewString.MString,NewBuffer,MaxLengthInBytes);
			NewString.MString.Length=LengthInBytes;

			RtlCopyUnicodeString(&NewString.MString,&MString);

			if (NT_SUCCESS(Status=RtlAppendUnicodeStringToString(&NewString.MString,&Operand.MString))!=FALSE)
			{
				NewString.MString.Buffer[LengthInChars]=NULL_CHAR;

				return(NewString);
			}
			else
			{
				DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION RtlAppendUnicodeStringToString() FAILED with STATUS [%X] !\n",Status);
				NewString.SetError();

				return(NewString);
			}
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION ExAllocatePoolWithTag() FAILED to ALLOCATE MEMORY !\n");
			NewString.SetError();

			return(NewString);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): OPERATOR+ FAILED because STRING (%d,%d) has ERROR FLAG set !\n",MErrorFlag,Operand.MErrorFlag);
		NewString.SetError();

		return(NewString);
	}
}
//-------------------------------------------------------------------------------------------------------
// If any of two OPERANDS has ERROR FLAG set, set ERROR FLAG to current OBJECT.
CUnicodeString& CUnicodeString::operator+=(const CUnicodeString& Operand)
{
	if (MErrorFlag==false && Operand.MErrorFlag==false)
	{
		*this=*this+Operand;

		return(*this);
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): OPERATOR+= FAILED because STRING (%d,%d) has ERROR FLAG set !\n",MErrorFlag,Operand.MErrorFlag);
		SetError();

		return(*this);
	}
}
//-------------------------------------------------------------------------------------------------------
// If Length including NULL_CHAR is EXCEEDED, FUNCTION returns NULL_CHAR.
// If ERROR FLAG, FUNCTION returns NULL_CHAR.
WCHAR CUnicodeString::operator[](int Index)
{
	if (MErrorFlag==false)
	{
		if (Index>=0 && Index<LengthInChars(true))
		{
			WCHAR												Char=MString.Buffer[Index];

			return(Char);
		}
		else
		{
			return(NULL_CHAR);
		}
	}
	else
	{
		DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): OPERATOR[] FAILED because STRING has ERROR FLAG set !\n");
		return(NULL_CHAR);
	}
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::operator PWSTR(void) const
{
	return(MString.Buffer);
}
//-------------------------------------------------------------------------------------------------------
CUnicodeString::operator const UNICODE_STRING&(void) const
{
	return(MString);
}
//-------------------------------------------------------------------------------------------------------
// If ERROR FLAG set, FUNCTION returns 0.
CUnicodeString::operator ULONG() const
{
	NTSTATUS													Status;

	if (MErrorFlag==false)
	{
		ULONG													Result;

		if (NT_SUCCESS(Status=RtlUnicodeStringToInteger((PUNICODE_STRING) &MString,0,&Result))!=FALSE)
		{
			return(Result);
		}
		else
		{
			DbgPrint(DRIVERLOGNAME " - FUNCTION " __FUNCTION__ "(): FUNCTION RtlUnicodeStringToInteger() FAILED with STATUS [%X] !\n",Status);

			return(0);
		}
	}
	else
	{
		return(0);
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CUnicodeString::Init(void)
{
	RtlInitEmptyUnicodeString(&MString,NULL,0);
	MErrorFlag=false;
}
//-------------------------------------------------------------------------------------------------------
// Sets ERROR FLAG ane MString to EMPTY STRING.
void CUnicodeString::SetError(void)
{
	Reset();

	MErrorFlag=true;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Resets ERROR FLAG.
void CUnicodeString::Reset(void)
{
	if (MString.Buffer!=NULL)
	{
		ExFreePool(MString.Buffer);
	}

	RtlInitEmptyUnicodeString(&MString,NULL,0);
	MErrorFlag=false;
}
//-------------------------------------------------------------------------------------------------------
// If ERROR FLAG set, FUNCTION returns 0, because MError contains EMPTY STRING.
USHORT CUnicodeString::LengthInBytes(bool IncludingNULLChar) const
{
	USHORT														LengthInBytes=MString.Length;

	if (IncludingNULLChar==true)
	{
		LengthInBytes+=CHAR_SIZE;
	}

	return(LengthInBytes);
}
//-------------------------------------------------------------------------------------------------------
// If ERROR FLAG set, FUNCTION returns 0, because MError contains EMPTY STRING.
USHORT CUnicodeString::LengthInChars(bool IncludingNULLChar) const
{
	USHORT														LengthInBytes=MString.Length;
	USHORT														LengthInChars=LengthInBytes/CHAR_SIZE;

	if (IncludingNULLChar==true)
	{
		LengthInChars++;
	}

	return(LengthInChars);
}
//-------------------------------------------------------------------------------------------------------
void CUnicodeString::DumpState(void) const
{
	DbgPrint("STRING [%p], ERROR FLAG [%d], LENGTH [%d], MAXIMUM LENGTH [%d], BUFFER [%S] !\n",this,MErrorFlag,MString.Length,MString.MaximumLength,MString.Buffer);
}
//-------------------------------------------------------------------------------------------------------
const UNICODE_STRING& CUnicodeString::GetUNICODE_STRING(void) const
{
	return(MString);
}
//-------------------------------------------------------------------------------------------------------
const WCHAR* CUnicodeString::GetUnicodeString(void) const
{
	return(MString.Buffer);
}
//-------------------------------------------------------------------------------------------------------