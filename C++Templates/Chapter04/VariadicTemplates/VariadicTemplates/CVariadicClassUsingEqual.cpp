//----------------------------------------------------------------------------------------------------------------------
#include "CVariadicClassUsingEqual.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CVariadicClassUsingEqual::operator()(const CVariadicClassUsing& Value1, const CVariadicClassUsing& Value2) const
{
	bool														Equals=(Value1.GetValue()==Value2.GetValue());

	return(Equals);
}
//----------------------------------------------------------------------------------------------------------------------