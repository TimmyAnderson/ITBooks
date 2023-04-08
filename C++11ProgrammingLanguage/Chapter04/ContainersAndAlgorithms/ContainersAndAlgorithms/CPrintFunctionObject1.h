//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
template<typename TType>
class CPrintFunctionObject1
{
//-----------------------------------------------------------------------------
	private:
		bool													MIsFirst;

	public:
		void operator()(const TType& Value)
		{
			if (MIsFirst==true)
			{
				MIsFirst=false;
			}
			else
			{
				std::wcout << L" ";
			}

			std::wcout << Value;
		}

	public:
		CPrintFunctionObject1(void)
			: MIsFirst(true)
		{
		}

		~CPrintFunctionObject1(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------