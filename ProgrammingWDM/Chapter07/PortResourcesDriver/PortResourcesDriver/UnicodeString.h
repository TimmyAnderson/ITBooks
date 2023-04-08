//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <Ntddk.h>
#include <wdm.h>
//-------------------------------------------------------------------------------------------------------
class CUnicodeString
{
	private:
		static const ULONG										STRING_TAG=' RTS';
		static const size_t										CHAR_SIZE=sizeof(WCHAR);
		static const WCHAR										NULL_CHAR=UNICODE_NULL;

	private:
		// FIELD MString ALWAYS contains NULL_CHAR.
		// FIELD MString.MaximumLength ALWAYS counting NULL_CHAR.
		UNICODE_STRING											MString;
		bool													MErrorFlag;

	public:
		void* operator new(size_t Size);
		void operator delete(void* Pointer);
		CUnicodeString operator=(const CUnicodeString& Operand);
		bool operator==(const CUnicodeString& Operand) const;
		CUnicodeString operator+(const CUnicodeString& Operand) const;
		CUnicodeString& operator+=(const CUnicodeString& Operand);
		WCHAR operator[](int Index);
		operator PWSTR(void) const;
		operator const UNICODE_STRING&(void) const;
		operator ULONG(void) const;

	private:
		void Init(void);
		void SetError(void);

	public:
		void Reset(void);
		USHORT LengthInBytes(bool IncludingNULLChar) const;
		USHORT LengthInChars(bool IncludingNULLChar) const;
		void DumpState(void) const;
		const UNICODE_STRING& GetUNICODE_STRING(void) const;
		const WCHAR* GetUnicodeString(void) const;

	public:
		explicit CUnicodeString(void);
		explicit CUnicodeString(const char* AnsiString);
		explicit CUnicodeString(PCWSTR UnicodeString);
		explicit CUnicodeString(ULONG Value);
		CUnicodeString(const CUnicodeString& Original);
		~CUnicodeString(void);
};
//-------------------------------------------------------------------------------------------------------