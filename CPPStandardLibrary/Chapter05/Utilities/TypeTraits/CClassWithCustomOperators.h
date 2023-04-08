//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CClassWithCustomOperators
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CClassWithCustomOperators operator+(const CClassWithCustomOperators& Other)
		{
			CClassWithCustomOperators							NewValue(MValue+Other.MValue);

			return(NewValue);
		}

		CClassWithCustomOperators operator+(int Other)
		{
			CClassWithCustomOperators							NewValue(MValue+Other);

			return(NewValue);
		}

	public:
		int GetValue(void)
		{
			return(MValue);
		}

	public:
		CClassWithCustomOperators(int Value)
			: MValue(Value)
		{
		}

		// !!! CLASS ma VIRTUAL METHOD (NIE JE TRIVIALLY COPYABLE), aby sa demonstrovalo, ze aj pre takyto typ CLASS funkcie na testovanie pritomnosti OPERATORS funguju.
		virtual ~CClassWithCustomOperators(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------