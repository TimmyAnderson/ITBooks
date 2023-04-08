//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS je DERIVED zo VSETKYCH SVOJICH TYPE PARAMETERS z TYPE PARAMETER PACK.
template<typename... TTypes>
class CDerivedVariadicTemplate : public TTypes...
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! CONSTRUCTOR vola vsetky CONSTRUCTORS pre BASE TYPES.
		CDerivedVariadicTemplate(const TTypes&... TypeParameters)
		// !!! Tento CODE sa transformuje na CODE [: TType_1(TypeParameter_1),TType_2(TypeParameter_2),...,TType_N(TypeParameter_N)].
			: TTypes(TypeParameters)...
		{
			std::wcout << L"CDerivedVariadicTemplate CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------