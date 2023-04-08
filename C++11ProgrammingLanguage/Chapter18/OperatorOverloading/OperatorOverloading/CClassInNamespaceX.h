//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CClassInNamespaceY.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
namespace X
{
//-----------------------------------------------------------------------------
	class CClassInNamespaceX final
	{
//-----------------------------------------------------------------------------
		private:
			int														MValue;

		public:
			CClassInNamespaceX operator+(const Y::CClassInNamespaceY& Value)
			{
				std::wcout << "MEMBER OPERATOR+ CALLED !" << std::endl;

				return(CClassInNamespaceX(MValue+Value.GetValue()));
			}

		public:
			int GetValue(void) const noexcept
			{
				return(MValue);
			}

		public:
			explicit CClassInNamespaceX(int Value)
				: MValue(Value)
			{
			}
//-----------------------------------------------------------------------------
	};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
	CClassInNamespaceX operator-(const CClassInNamespaceX& Left, const Y::CClassInNamespaceY& Right)
	{
		std::wcout << "NON-MEMBER OPERATOR- CALLED !" << std::endl;

		return(CClassInNamespaceX(Left.GetValue()-Right.GetValue()));
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------