//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
class CConstExpressionMethod
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! KEYWORD [constexpr] je mozne aplikovat na STATIC METHODS.
		constexpr static int GetSizeStatic(int Size)
		{
			// !!! V C++ 11 moze FUNCTION s KEYWORD [constexpr] obsahovat IBA RETURN STATEMENT.
			return((Size>0) ? Size : 1);
		}

		// !!! KEYWORD [constexpr] je mozne aplikovat na INSTANCE METHODS, ktore vsa MUSIA byt NONSTATIC.
		constexpr int GetSize(int Size) const
		{
			// !!! V C++ 11 moze FUNCTION s KEYWORD [constexpr] obsahovat IBA RETURN STATEMENT.
			return((Size>0) ? Size : 1);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------