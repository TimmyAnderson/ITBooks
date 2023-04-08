//-----------------------------------------------------------------------------
#include "CInClassInitializers.h"
//-----------------------------------------------------------------------------
int																GlobalVariable=555;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! MEMBER INITIALIZER LIST sa pouziva pre prve 2 FIELDS, a preto sa IN CLASS INITIALIZERS POUZIJU pre posledne 2 FIELDS.
CInClassInitializers::CInClassInitializers(int Value1, int Value2)
	: MValue1(Value1), MValue2(Value2)
{
	std::wcout << L"CONSTRUCTOR CInClassInitializers with 2 PARAMETERS CALLED !" << std::endl;
}
//-----------------------------------------------------------------------------
// !!! MEMBER INITIALIZER LIST sa pouziva pre VSETKY FIELDS, a preto sa IN CLASS INITIALIZERS NEPOUZIJU.
CInClassInitializers::CInClassInitializers(int Value1, int Value2, int Value3, int Value4)
	: MValue1(Value1), MValue2(Value2), MValue3(Value3), MValue4(Value4)
{
	std::wcout << L"CONSTRUCTOR CInClassInitializers with 4 PARAMETERS CALLED !" << std::endl;
}
//-----------------------------------------------------------------------------
// !!! Kedze CONSTRUCTOR NENASTAVUJE hodnoty FIELDS v MEMBER INITIALIZER LIST, ale inicializacia sa vykonava volanim OPERATOR=, IN CLASS INITIALIZERS sa v tomto pripade POUZIJU.
CInClassInitializers::CInClassInitializers(int Value1, int Value2, int Value3, int Value4, int)
{
	std::wcout << L"CONSTRUCTOR CInClassInitializers with 5 PARAMETERS CALLED - BEGIN !" << std::endl;

	MValue1=Value1;
	MValue2=Value2;
	MValue3=Value3;
	MValue4=Value4;

	std::wcout << L"CONSTRUCTOR CInClassInitializers with 5 PARAMETERS CALLED - END !" << std::endl;
}
//-----------------------------------------------------------------------------
CInClassInitializers::~CInClassInitializers(void)
{
	std::wcout << L"DESTRUCTOR ~CInClassInitializers CALLED !" << std::endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const CField1& CInClassInitializers::GetValue1(void) const noexcept
{
	return(MValue1);
}
//-----------------------------------------------------------------------------
const CField2& CInClassInitializers::GetValue2(void) const noexcept
{
	return(MValue2);
}
//-----------------------------------------------------------------------------
const CField3& CInClassInitializers::GetValue3(void) const noexcept
{
	return(MValue3);
}
//-----------------------------------------------------------------------------
const CField4& CInClassInitializers::GetValue4(void) const noexcept
{
	return(MValue4);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int GlobalFunction(void)
{
	return(888);
}
//-----------------------------------------------------------------------------