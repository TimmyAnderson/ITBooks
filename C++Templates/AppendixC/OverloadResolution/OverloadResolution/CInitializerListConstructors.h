//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <initializer_list>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CInitializerListConstructors final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::vector<TType>										MList;
		unsigned int											MValue1;
		TType													MValue2;

	public:
		const std::vector<TType>& GetList(void) const noexcept;
		unsigned int GetValue1(void) const noexcept;
		const TType& GetValue2(void) const noexcept;

	public:
		CInitializerListConstructors(std::initializer_list<TType> Values);
		CInitializerListConstructors(unsigned int Value1, const TType& Value2);
		virtual ~CInitializerListConstructors(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CInitializerListConstructors<TType>::CInitializerListConstructors(std::initializer_list<TType> Values)
	: MList(Values), MValue1(), MValue2()
{
	std::wcout << L"CONSTRUCTOR [CInitializerListConstructors(initializer_list<TType> Values)] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CInitializerListConstructors<TType>::CInitializerListConstructors(unsigned int Value1, const TType& Value2)
	: MList(), MValue1(Value1), MValue2(Value2)
{
	std::wcout << L"CONSTRUCTOR [CInitializerListConstructors(unsigned int Value1, const TType& Value2)] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CInitializerListConstructors<TType>::~CInitializerListConstructors(void) noexcept
{
	std::wcout << L"DESTRUCTOR [~CInitializerListConstructors(void) noexcept] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const std::vector<TType>& CInitializerListConstructors<TType>::GetList(void) const noexcept
{
	return(MList);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
unsigned int CInitializerListConstructors<TType>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CInitializerListConstructors<TType>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------