//----------------------------------------------------------------------------------------------------------------------
#include "TestsStringOperations.h"
#include <wdm.h>
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString1(void)
{
	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												String;

	// !!! FUNCITON iba nastavuje FIELDS TYPE [UNICODE_STRING] nealokuje vsak BUFFER.
	// !!! FIELD [String.Length] obsahuje dlzku STRING v BYTES bez NULL TERMINATOR.
	// !!! FIELD [String.MaximumLength] obsahuje dlzku BUFFER v BYTES s NULL TERMINATOR.
	RtlInitUnicodeString(&String,L"Some TEXT !");
	
	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString2(void)
{
	const char*													FunctionName=__FUNCTION__;
	constexpr SIZE_T											MY_BUFFER_SIZE=200;

	UNICODE_STRING												SourceString;

	RtlInitUnicodeString(&SourceString,L"Some TEXT !");

	UNICODE_STRING												String;

	// !!! Alokuje sa MEMORY BUFFER.
	String.Buffer=(PWCH)ExAllocatePool2(POOL_FLAG_PAGED,MY_BUFFER_SIZE,MY_TAG);

	if (String.Buffer==nullptr)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER !!!\n",FunctionName));
		return;
	}

	String.Length=0;
	String.MaximumLength=MY_BUFFER_SIZE;

	// !!! Vykona kopiu CHARACTERS vo FIELD [SourceString::Buffer] do FIELD [String::Buffer].
	// !!! Nastavuje VALUE FIELD [String::Length].
	// !!! Nemeni VALUE FIELD [String::MaximumLength].
	RtlCopyUnicodeString(&String,&SourceString);

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));

	// !!! Uvolni sa MEMORY BUFFER.
	ExFreePoolWithTag(String.Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString3(void)
{
	const char*													FunctionName=__FUNCTION__;
	constexpr SIZE_T											MY_BUFFER_SIZE=200;

	PCWSTR														CString=L" ";
	UNICODE_STRING												SourceString1;
	UNICODE_STRING												SourceString2;

	RtlInitUnicodeString(&SourceString1,L"Timmy");
	RtlInitUnicodeString(&SourceString2,L"Anderson");

	UNICODE_STRING												String;

	// !!! Alokuje sa MEMORY BUFFER.
	String.Buffer=(PWCH)ExAllocatePool2(POOL_FLAG_PAGED,MY_BUFFER_SIZE,MY_TAG);

	if (String.Buffer==nullptr)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER !!!\n",FunctionName));
		return;
	}

	String.Length=0;
	String.MaximumLength=MY_BUFFER_SIZE;

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));

	{
		// !!! Do UNICODE STRING sa prida dalsi UNICODE STRING.
		NTSTATUS												Result=RtlAppendUnicodeStringToString(&String,&SourceString1);

		if (NT_SUCCESS(Result)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED APPEND UNICODE STRING 1 !!!\n",FunctionName));
		}
	}

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));

	{
		// !!! Do UNICODE STRING sa prida C-STRING.
		NTSTATUS												Result=RtlAppendUnicodeToString(&String,CString);

		if (NT_SUCCESS(Result)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED APPEND C-STRING !!!\n",FunctionName));
		}
	}

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));

	{
		// !!! Do UNICODE STRING sa prida dalsi UNICODE STRING.
		NTSTATUS												Result=RtlAppendUnicodeStringToString(&String,&SourceString2);

		if (NT_SUCCESS(Result)==false)
		{
			KdPrint(("!!!!! FUNCTION [%s] FAILED APPEND UNICODE STRING 2 !!!\n",FunctionName));
		}
	}

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] LENGTH [%hu] MAX LENGTH [%hu] BUFFER [%p] !!!\n",FunctionName,String,String.Length,String.MaximumLength,String.Buffer));

	// !!! Uvolni sa MEMORY BUFFER.
	ExFreePoolWithTag(String.Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString4CompareStrings(const char* FunctionName, PUNICODE_STRING String1, PUNICODE_STRING String2, BOOLEAN CaseInSensitive)
{
	LONG														Result=RtlCompareUnicodeString(String1,String2,CaseInSensitive);
	UNICODE_STRING												ResultString;

	if (Result<0)
	{
		RtlInitUnicodeString(&ResultString,L"is LOWER than");
	}
	else if (Result>0)
	{
		RtlInitUnicodeString(&ResultString,L"is GREATER than");
	}
	else
	{
		RtlInitUnicodeString(&ResultString,L"is EQUAL to");
	}

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] %wZ STRING [%wZ] ! RESULT [%ld] CASE INSENSITIVE [%d] !!!\n",FunctionName,String1,ResultString,String2,Result,CaseInSensitive));
}
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString4(void)
{
	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												SourceString1;
	UNICODE_STRING												SourceString2;
	UNICODE_STRING												SourceString3;
	UNICODE_STRING												SourceString4;

	RtlInitUnicodeString(&SourceString1,L"Timmy");
	RtlInitUnicodeString(&SourceString2,L"Timmy");
	RtlInitUnicodeString(&SourceString3,L"Anderson");
	RtlInitUnicodeString(&SourceString4,L"TIMMY");

	TestsUnicodeString4CompareStrings(FunctionName,&SourceString1,&SourceString2,FALSE);

	TestsUnicodeString4CompareStrings(FunctionName,&SourceString1,&SourceString3,FALSE);

	TestsUnicodeString4CompareStrings(FunctionName,&SourceString3,&SourceString1,FALSE);

	TestsUnicodeString4CompareStrings(FunctionName,&SourceString1,&SourceString4,FALSE);

	TestsUnicodeString4CompareStrings(FunctionName,&SourceString1,&SourceString4,TRUE);
}
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString5EqualStrings(const char* FunctionName, PUNICODE_STRING String1, PUNICODE_STRING String2, BOOLEAN CaseInSensitive)
{
	BOOLEAN														Result=RtlEqualUnicodeString(String1,String2,CaseInSensitive);
	UNICODE_STRING												ResultString;

	if (Result==TRUE)
	{
		RtlInitUnicodeString(&ResultString,L"is EQUAL to");
	}
	else
	{
		RtlInitUnicodeString(&ResultString,L"is NOT EQUAL to");
	}

	KdPrint(("!!!!! FUNCTION [%s] STRING [%wZ] %wZ STRING [%wZ] ! CASE INSENSITIVE [%d] !!!\n",FunctionName,String1,ResultString,String2,CaseInSensitive));
}
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString5(void)
{
	const char*													FunctionName=__FUNCTION__;

	UNICODE_STRING												SourceString1;
	UNICODE_STRING												SourceString2;
	UNICODE_STRING												SourceString3;
	UNICODE_STRING												SourceString4;

	RtlInitUnicodeString(&SourceString1,L"Timmy");
	RtlInitUnicodeString(&SourceString2,L"Timmy");
	RtlInitUnicodeString(&SourceString3,L"Anderson");
	RtlInitUnicodeString(&SourceString4,L"TIMMY");

	TestsUnicodeString5EqualStrings(FunctionName,&SourceString1,&SourceString2,FALSE);

	TestsUnicodeString5EqualStrings(FunctionName,&SourceString1,&SourceString3,FALSE);

	TestsUnicodeString5EqualStrings(FunctionName,&SourceString1,&SourceString4,FALSE);

	TestsUnicodeString5EqualStrings(FunctionName,&SourceString1,&SourceString4,TRUE);
}
//----------------------------------------------------------------------------------------------------------------------
void TestsUnicodeString6(void)
{
	const char*													FunctionName=__FUNCTION__;
	constexpr SIZE_T											MY_BUFFER_SIZE=200;
	constexpr size_t											MY_BUFFER_SIZE_IN_WORDS=(MY_BUFFER_SIZE/sizeof(WCHAR));

	PWCHAR														Buffer;

	Buffer=(PWCHAR)ExAllocatePool2(POOL_FLAG_PAGED,MY_BUFFER_SIZE,MY_TAG);

	if (Buffer==nullptr)
	{
		KdPrint(("!!!!! FUNCTION [%s] FAILED to ALLOCATE BUFFER !!!\n",FunctionName));
		return;
	}

	PCWCHAR														SourceString=L"Some TEXT !";

	wcscpy_s(Buffer,MY_BUFFER_SIZE_IN_WORDS,SourceString);
	
	size_t														SourceStringLength=wcsnlen_s(Buffer,MY_BUFFER_SIZE_IN_WORDS);

	KdPrint(("!!!!! FUNCTION [%s] STRING [%S] LENGTH [%Iu] !!!\n",FunctionName,Buffer,SourceStringLength));

	ExFreePoolWithTag(Buffer,MY_TAG);
}
//----------------------------------------------------------------------------------------------------------------------