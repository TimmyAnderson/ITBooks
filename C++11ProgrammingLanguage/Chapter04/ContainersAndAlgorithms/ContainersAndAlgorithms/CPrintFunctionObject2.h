//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
template<typename TType>
class CPrintFunctionObject2
{
//-----------------------------------------------------------------------------
	private:
		bool													MIsFirst;

	public:
		// FOREACH umoznuje prenost VALUES aj BY-VALUE namiesto BY-REFERENCE.
		void operator()(TType Value)
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
		CPrintFunctionObject2(void)
			: MIsFirst(true)
		{
		}

		~CPrintFunctionObject2(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------