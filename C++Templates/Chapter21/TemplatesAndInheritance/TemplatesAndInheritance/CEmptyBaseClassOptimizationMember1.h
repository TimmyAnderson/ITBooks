//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CEmptyBaseClassOptimizationMember1Empty final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CEmptyBaseClassOptimizationMember1NonTemplate
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CEmptyBaseClassOptimizationMember1Empty					MField1;
		CEmptyBaseClassOptimizationMember1Empty					MField2;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CEmptyBaseClassOptimizationMember1Template
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		TType													MField1;
		TType													MField2;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------