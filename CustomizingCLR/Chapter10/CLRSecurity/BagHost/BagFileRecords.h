//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include "BagFileRecord.h"
//------------------------------------------------------------------------------------------------------
class CBagFileRecords
{
	private:
		std::wstring											MBagExecutable;
		std::wstring											MRunnableType;
		std::vector<CBagFileRecord*>							MBagFileRecords;

	public:
		std::wstring GetBagExecutable(void);
		std::wstring GetRunnableType(void);
		std::vector<CBagFileRecord*>& GetBagFileRecords(void);
		void SetBagExecutable(std::wstring Value);
		void SetRunnableType(std::wstring Value);

	public:
		CBagFileRecords(void);
		~CBagFileRecords(void);
};
//------------------------------------------------------------------------------------------------------