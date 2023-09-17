//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CParsingDependentNamesTemplatesLevel1 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		template<int M>
		class CParsingDependentNamesTemplatesLevel2 final
		{
//----------------------------------------------------------------------------------------------------------------------
			public:
				template<int N>
				class CParsingDependentNamesTemplatesLevel3
				{
//----------------------------------------------------------------------------------------------------------------------
					public:
						virtual void Test(const std::wstring& Text) const;
//----------------------------------------------------------------------------------------------------------------------
				};
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<int M>
template<int N>
void CParsingDependentNamesTemplatesLevel1<TType>::CParsingDependentNamesTemplatesLevel2<M>::CParsingDependentNamesTemplatesLevel3<N>::Test(const std::wstring& Text) const
{
	std::wcout << Text << L" TYPE [" << GetTypeInfoName<TType>() << L"] M [" << M << L"] N [" << N << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int M, int N>
class CParsingDependentNamesTemplatesLevelTest final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Test1(void) const;
		void Test2(void) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int M, int N>
void CParsingDependentNamesTemplatesLevelTest<TType,M,N>::Test1(void) const
{
	// !!!!! MUSI byt pouzity KEYWORD [typename] aj KEYWORD [template].
	typename CParsingDependentNamesTemplatesLevel1<TType>::template CParsingDependentNamesTemplatesLevel2<M>::template CParsingDependentNamesTemplatesLevel3<N>	Object;

	// !!!!! MUSI byt pouzity KEYWORD [typename] aj KEYWORD [template].
	typename CParsingDependentNamesTemplatesLevel1<TType>::template CParsingDependentNamesTemplatesLevel2<M>::template CParsingDependentNamesTemplatesLevel3<N>*	Pointer=&Object;

	// !!!!! METHOD NEBUDE volana VIRTUALNE.
	//Pointer->template CParsingDependentNamesTemplatesLevel3<N>::Test(L"TEST 1");

	Pointer->Test(L"TEST 1");
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int M, int N>
void CParsingDependentNamesTemplatesLevelTest<TType,M,N>::Test2(void) const
{
	// !!!!! MUSI byt pouzity KEYWORD [typename] aj KEYWORD [template].
	typename CParsingDependentNamesTemplatesLevel1<TType>::template CParsingDependentNamesTemplatesLevel2<M>::template CParsingDependentNamesTemplatesLevel3<N>	Object;

	// !!!!! MUSI byt pouzity KEYWORD [typename] aj KEYWORD [template].
	typename CParsingDependentNamesTemplatesLevel1<TType>::template CParsingDependentNamesTemplatesLevel2<M>::template CParsingDependentNamesTemplatesLevel3<N>&	Reference=Object;

	// !!!!! METHOD NEBUDE volana VIRTUALNE.
	//Reference.template CParsingDependentNamesTemplatesLevel3<N>::Test(L"TEST 2");

	Reference.Test(L"TEST 2");
}
//----------------------------------------------------------------------------------------------------------------------