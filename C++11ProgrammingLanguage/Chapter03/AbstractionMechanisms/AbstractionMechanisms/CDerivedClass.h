//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <sstream>
#include "CBaseClass.h"
//-----------------------------------------------------------------------------
class CDerivedClass : public CBaseClass
{
//-----------------------------------------------------------------------------
	private:
		int														MValueDerived;

	public:
		// VIRTUAL METHOD.
		virtual std::wstring Print(void) const override
		{
			std::wstringstream									Stream;

			Stream << L"VALUE BASE [" << GetValueBase() << L"] VALUE DERIVED [" << GetValueDerived() << L"] !";

			return(Stream.str());
		}

	public:
		int GetValueDerived(void) const
		{
			return(MValueDerived);
		}

	public:
		CDerivedClass(void)
			: CBaseClass(), MValueDerived(0)
		{
		}

		CDerivedClass(int ValueBase, int ValueDerived)
			: CBaseClass(ValueBase), MValueDerived(ValueDerived)
		{
		}

		virtual ~CDerivedClass(void) override
		{
			std::wcout << L"DESTRUCTOR CDerivedClass CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------