//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CPureVirtualBase
{
//-----------------------------------------------------------------------------
	public:
		virtual void PureVirtualMethod(void) const=0;

		// !!!!! C++ podporuje PURE VIRTUAL METHODS s DEFINITION, avsak ta MUSI byt v .CPP FILE. V .H FILE je to ERROR, aj ked VC++ to akceptuje.
		virtual void PureVirtualMethodWithDefinition(void) const=0;

	public:
		CPureVirtualBase(void)
		{
		}

		virtual ~CPureVirtualBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------