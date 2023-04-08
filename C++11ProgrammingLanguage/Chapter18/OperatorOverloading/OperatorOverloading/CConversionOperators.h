//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CConversionOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		// IMPLICIT CONVERSION OPERATOR.
		operator int(void) const
		{
			std::wcout << "IMPLICIT CONVERSION OPERATOR INT() CALLED !" << std::endl;

			return(MValue);
		}

		// EXPLICIT CONVERSION OPERATOR.
		explicit operator short(void) const
		{
			std::wcout << "EXPLICIT CONVERSION OPERATOR SHORT() CALLED !" << std::endl;

			return(static_cast<short>(MValue));
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CConversionOperators(void)
			: MValue()
		{
		}

		CConversionOperators(int Value)
			: MValue(Value)
		{
		}

		// IMPLICIT CONVERSION CONSTRUCTOR.
		CConversionOperators(short Value)
			: MValue(Value)
		{
			std::wcout << "IMPLICIT CONVERSION CONSTRUCTOR SHORT CALLED !" << std::endl;
		}

		// EXPLICIT CONVERSION CONSTRUCTOR.
		explicit CConversionOperators(double Value)
			: MValue(static_cast<int>(Value))
		{
			std::wcout << "EXPLICIT CONVERSION CONSTRUCTOR DOUBLE CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------