//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include <stdio.h>
#include "IEquatable.h"
//-------------------------------------------------------------------------------------------------------
class CEquatableClass2 : public IEquatable
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual bool Equals(const IEquatable& Other)
		{
			try
			{
				const CEquatableClass2&							TypedOther=dynamic_cast<const CEquatableClass2&>(Other);

				if (MValue==TypedOther.MValue)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
			catch(...)
			{
				wprintf_s(L"EXCEPTION was CAUGHT !\n");
				return(false);
			}
		}

	public:
		CEquatableClass2(std::wstring Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------