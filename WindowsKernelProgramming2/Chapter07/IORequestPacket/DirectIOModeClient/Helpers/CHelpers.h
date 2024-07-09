//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Windows.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CHelpers final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		static bool SendSynchronousDeviceIoControlRequest(const wchar_t* SymbolicLinkName, DWORD Code, BYTE* InputBuffer, DWORD InputBufferSize, BYTE* OutputBuffer, DWORD OutputBufferSize, DWORD* BytesReturned);
		static bool SendAsynchronousDeviceIoControlRequest(const wchar_t* SymbolicLinkName, DWORD Code, BYTE* InputBuffer, DWORD InputBufferSize, BYTE* OutputBuffer, DWORD OutputBufferSize, DWORD* BytesReturned);

	public:
		static bool SendSynchronousDeviceIoControlRequestEmptyArrays(const wchar_t* SymbolicLinkName, DWORD Code);
		static bool SendAsynchronousDeviceIoControlRequestEmptyArrays(const wchar_t* SymbolicLinkName, DWORD Code);

	public:
		static bool SendSynchronousReadRequest(const wchar_t* SymbolicLinkName, BYTE* ReadBuffer, DWORD ReadBufferSize, DWORD* NumberOfBytesRead);
		static bool SendSynchronousWriteRequest(const wchar_t* SymbolicLinkName, const BYTE* WriteBuffer, DWORD WriteBufferSize, DWORD* NumberOfBytesWritten);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------