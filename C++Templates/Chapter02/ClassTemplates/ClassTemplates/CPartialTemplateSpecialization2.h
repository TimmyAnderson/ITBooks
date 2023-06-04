//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CPartialTemplateSpecialization2
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		TType1 Get1(void) const noexcept;
		void Set1(TType1 Value) noexcept;
		TType2 Get2(void) const noexcept;
		void Set2(TType2 Value) noexcept;

	public:
		CPartialTemplateSpecialization2(void)
			: MValue1(), MValue2()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 CPartialTemplateSpecialization2<TType1,TType2>::Get1(void) const noexcept
{
	std::wcout << L"TEMPLATE METHOD [TType1 Get1(void) const noexcept] CALLED !" << std::endl;

	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecialization2<TType1,TType2>::Set1(TType1 Value) noexcept
{
	std::wcout << L"TEMPLATE METHOD [void Set1(TType1 Value) noexcept] CALLED !" << std::endl;

	MValue1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 CPartialTemplateSpecialization2<TType1,TType2>::Get2(void) const noexcept
{
	std::wcout << L"TEMPLATE METHOD [TType2 Get2(void) const noexcept] CALLED !" << std::endl;

	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecialization2<TType1,TType2>::Set2(TType2 Value) noexcept
{
	std::wcout << L"TEMPLATE METHOD [void Set2(TType2 Value) noexcept] CALLED !" << std::endl;

	MValue2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS pre TYPE [TType1*] a [TType2*].
template<typename TType1, typename TType2>
class CPartialTemplateSpecialization2<TType1*,TType2*>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1*													MValue1;
		TType2*													MValue2;

	public:
		TType1* Get1(void) const noexcept;
		void Set1(TType1* Value) noexcept;
		TType2* Get2(void) const noexcept;
		void Set2(TType2* Value) noexcept;

	public:
		CPartialTemplateSpecialization2(void)
			: MValue1(), MValue2()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1* CPartialTemplateSpecialization2<TType1*,TType2*>::Get1(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [TType1* Get1(void) const noexcept] CALLED !" << std::endl;

	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecialization2<TType1*,TType2*>::Set1(TType1* Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set1(TType1* Value) noexcept] CALLED !" << std::endl;

	MValue1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2* CPartialTemplateSpecialization2<TType1*,TType2*>::Get2(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [TType2* Get2(void) const noexcept] CALLED !" << std::endl;

	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
void CPartialTemplateSpecialization2<TType1*,TType2*>::Set2(TType2* Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set2(TType2* Value) noexcept] CALLED !" << std::endl;

	MValue2=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARTIAL SPECIALIZATION TEMPLATE CLASS pre TYPE [TType] a [double].
template<typename TType>
class CPartialTemplateSpecialization2<TType,double>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue1;
		double													MValue2;

	public:
		TType Get1(void) const noexcept;
		void Set1(TType Value) noexcept;
		double Get2(void) const noexcept;
		void Set2(double Value) noexcept;

	public:
		CPartialTemplateSpecialization2(void)
			: MValue1(), MValue2()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType CPartialTemplateSpecialization2<TType,double>::Get1(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [TType Get1(void) const noexcept] CALLED !" << std::endl;

	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecialization2<TType,double>::Set1(TType Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set1(TType Value) noexcept] CALLED !" << std::endl;

	MValue1=Value;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
double CPartialTemplateSpecialization2<TType,double>::Get2(void) const noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [double Get2(void) const noexcept] CALLED !" << std::endl;

	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CPartialTemplateSpecialization2<TType,double>::Set2(double Value) noexcept
{
	std::wcout << L"TEMPLATE SPECIALIZATION METHOD [void Set2(double Value) noexcept] CALLED !" << std::endl;

	MValue2=Value;
}
//----------------------------------------------------------------------------------------------------------------------