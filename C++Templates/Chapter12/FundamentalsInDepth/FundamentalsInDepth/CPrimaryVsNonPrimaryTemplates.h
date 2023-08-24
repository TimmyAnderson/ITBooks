//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je PRIMARY TEMPLATE CLASS, lebo ziaden TEMPLATE PARAMETER NIE JE SPECIALIZED.
template<typename TType1, typename TType2>
class CPrimaryVsNonPrimaryTemplates final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MPrint;
		TType1													MField1;
		TType2													MField2;

	public:
		const TType1& GetField1(void) const noexcept;
		void SetField1(const TType1& Value) noexcept;
		const TType2& GetField2(void) const noexcept;
		void SetField2(const TType2& Value) noexcept;

	public:
		CPrimaryVsNonPrimaryTemplates(bool Print, TType1 Field1, TType2 Field2);
		virtual ~CPrimaryVsNonPrimaryTemplates(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPrimaryVsNonPrimaryTemplates<TType1,TType2>::CPrimaryVsNonPrimaryTemplates(bool Print, TType1 Field1, TType2 Field2)
	: MPrint(Print), MField1(Field1), MField2(Field2)
{
	if (MPrint==true)
	{
		std::wcout << L"PRIMARY TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CPrimaryVsNonPrimaryTemplates<TType1,TType2>::~CPrimaryVsNonPrimaryTemplates(void) noexcept
{
	if (MPrint==true)
	{
		std::wcout << L"PRIMARY TEMPLATE DESTRUCTOR CALLED !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CPrimaryVsNonPrimaryTemplates<TType1,TType2>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPrimaryVsNonPrimaryTemplates<TType1,TType2>::SetField1(const TType1& Value) noexcept
{
	MField1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CPrimaryVsNonPrimaryTemplates<TType1,TType2>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPrimaryVsNonPrimaryTemplates<TType1,TType2>::SetField2(const TType2& Value) noexcept
{
	MField2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je NON-PRIMARY TEMPLATE CLASS, lebo jeden TEMPLATE PARAMETER JE SPECIALIZED.
template<typename TType>
class CPrimaryVsNonPrimaryTemplates<TType,double> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MPrint;
		TType													MField1;
		double													MField2;

	public:
		const TType& GetField1(void) const noexcept;
		void SetField1(const TType& Value) noexcept;
		const double& GetField2(void) const noexcept;
		void SetField2(const double& Value) noexcept;

	public:
		CPrimaryVsNonPrimaryTemplates(bool Print, TType Field1, double Field2);
		virtual ~CPrimaryVsNonPrimaryTemplates(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPrimaryVsNonPrimaryTemplates<TType,double>::CPrimaryVsNonPrimaryTemplates(bool Print, TType Field1, double Field2)
	: MPrint(Print), MField1(Field1), MField2(Field2)
{
	if (MPrint==true)
	{
		std::wcout << L"NON-PRIMARY TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CPrimaryVsNonPrimaryTemplates<TType,double>::~CPrimaryVsNonPrimaryTemplates(void) noexcept
{
	if (MPrint==true)
	{
		std::wcout << L"NON-PRIMARY TEMPLATE DESTRUCTOR CALLED !" << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CPrimaryVsNonPrimaryTemplates<TType,double>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPrimaryVsNonPrimaryTemplates<TType,double>::SetField1(const TType& Value) noexcept
{
	MField1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const double& CPrimaryVsNonPrimaryTemplates<TType,double>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPrimaryVsNonPrimaryTemplates<TType,double>::SetField2(const double& Value) noexcept
{
	MField2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je PRIMARY TEMPLATE VARIABLE, lebo ziaden TEMPLATE PARAMETER NIE JE SPECIALIZED.
template<typename TType1, typename TType2>
CPrimaryVsNonPrimaryTemplates<TType1,TType2>					PrimaryVsNonPrimaryTemplatesVariable=CPrimaryVsNonPrimaryTemplates<TType1,TType2>(false,TType1(),TType2());
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je NON-PRIMARY TEMPLATE VARIABLE, lebo jeden TEMPLATE PARAMETER JE SPECIALIZED.
template<typename TType>
CPrimaryVsNonPrimaryTemplates<TType,double>						PrimaryVsNonPrimaryTemplatesVariable<TType,double> =CPrimaryVsNonPrimaryTemplates<TType,double>(false,TType(),double());
//----------------------------------------------------------------------------------------------------------------------