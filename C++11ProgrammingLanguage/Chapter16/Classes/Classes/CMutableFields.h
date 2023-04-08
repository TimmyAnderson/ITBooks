//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CMutableFields final
{
//-----------------------------------------------------------------------------
	private:
		mutable int												MMutableField;

	public:
		int GetMutableField(void) const noexcept
		{
			return(MMutableField);
		}

		void SetMutableField(int Value) const noexcept
		{
			// !!! Aj NAPRIEK tomu, ze METHOD je CONST METHOD, kedze FIELD je MUTABLE FIELD, tak METHOD MOZE nastavit VALUE MUTABLE FIELD.
			MMutableField=Value;
		}

	public:
		CMutableFields(int MutableField)
			: MMutableField(MutableField)
		{
		}

		~CMutableFields(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------