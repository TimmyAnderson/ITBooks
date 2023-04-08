//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CConcreteType
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CConcreteType& operator=(const CConcreteType& Other)
		{
			std::wcout << L"COPY OPERATOR= CALLED !" << std::endl;

			MValue=Other.MValue;

			return(*this);
		}

		CConcreteType& operator=(CConcreteType&& Other)
		{
			std::wcout << L"MOVE OPERATOR= CALLED !" << std::endl;

			MValue=std::move(Other.MValue);

			return(*this);
		}

		bool operator<(const CConcreteType& Other)
		{
			if (MValue<Other.MValue)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}

	public:
		int GetValue(void) const
		{
			return(MValue);
		}

	public:
		CConcreteType(void)
			: MValue(0)
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CConcreteType(int Value)
			: MValue(Value)
		{
			std::wcout << L"CONSTRUCTOR CALLED !" << std::endl;
		}

		CConcreteType(const CConcreteType& Value)
			: MValue(Value.MValue)
		{
		}

		CConcreteType(CConcreteType&& Value)
			: MValue(std::move(Value.MValue))
		{
		}

		~CConcreteType(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
inline std::wostream& operator<<(std::wostream& Stream, const CConcreteType& Value)
{
	Stream << Value.GetValue();

	return(Stream);
}
//-----------------------------------------------------------------------------
inline bool operator==(const CConcreteType& Value1, const CConcreteType& Value2)
{
	if (Value1.GetValue()==Value2.GetValue())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
inline bool operator<(const CConcreteType& Value1, const CConcreteType& Value2)
{
	if (Value1.GetValue()<Value2.GetValue())
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------