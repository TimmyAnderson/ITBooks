//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class CComplexClass
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CComplexClass& operator=(const CComplexClass& Value)
		{
			MValue=Value.MValue;

			std::wcout << "COPY OPERATOR= CALLED !" << std::endl;

			return(*this);
		}

		CComplexClass& operator=(CComplexClass&& Value)
		{
			MValue=Value.MValue;

			std::wcout << "MOVE OPERATOR= CALLED !" << std::endl;

			return(*this);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

		void SetValue(int Value) noexcept
		{
			MValue=Value;
		}

	public:
		CComplexClass(int Value)
			: MValue(Value)
		{
			std::wcout << "DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CComplexClass(const CComplexClass& Value)
			: MValue(Value.MValue)
		{
			std::wcout << "COPY CONSTRUCTOR CALLED !" << std::endl;
		}

		CComplexClass(CComplexClass&& Value)
			: MValue(Value.MValue)
		{
			std::wcout << "MOVE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CComplexClass& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-------------------------------------------------------------------------------------------------------