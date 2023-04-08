//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CField1.h"
#include "CField2.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CDefaultInitialization final
{
//-----------------------------------------------------------------------------
	public:
		CField1													MObject1;
		CField2													MObject2;
		int														MPrimitiveType1;
		double													MPrimitiveType2;

	public:
		const CField1& GetObject1(void) const noexcept
		{
			return(MObject1);
		}

		const CField2& GetObject2(void) const noexcept
		{
			return(MObject2);
		}

		int GetPrimitiveType1(void) const noexcept
		{
			return(MPrimitiveType1);
		}

		double GetPrimitiveType2(void) const noexcept
		{
			return(MPrimitiveType2);
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------