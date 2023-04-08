//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
class CBaseClass
{
//-----------------------------------------------------------------------------
	private:
		int														MValueBase;

	public:
		// VIRTUAL METHOD.
		virtual std::wstring Print(void) const=0;

	public:
		int GetValueBase(void) const
		{
			return(MValueBase);
		}

	public:
		CBaseClass(void)
			: MValueBase(0)
		{
		}

		CBaseClass(int ValueBase)
			: MValueBase(ValueBase)
		{
		}

		virtual ~CBaseClass(void)
		{
			std::wcout << L"DESTRUCTOR CBaseClass CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------