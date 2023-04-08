//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CMethodHidingUncoverBase
{
//-----------------------------------------------------------------------------
	protected:
		void ProtectedMethod(int) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverBase::ProtectedMethod(INT) CALLED !" << std::endl;
		}

	public:
		void Method1(int) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverBase::Method1(INT) CALLED !" << std::endl;
		}

		void Method2(int,int) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverBase::Method2(INT,INT) CALLED !" << std::endl;
		}

		void PublicMethod(int) const
		{
			std::wcout << L"METHOD CMethodHidingUncoverBase::PublicMethod(INT) CALLED !" << std::endl;
		}

	public:
		CMethodHidingUncoverBase(void)
		{
		}

		virtual ~CMethodHidingUncoverBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------