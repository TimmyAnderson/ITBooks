#pragma once
//------------------------------------------------------------------------------
struct CSharedData
{
	BYTE*					Buffer;
	OVERLAPPED				Overlapped;
	HANDLE					CP;
	HANDLE					File;
	DWORD					Size;
};
//------------------------------------------------------------------------------