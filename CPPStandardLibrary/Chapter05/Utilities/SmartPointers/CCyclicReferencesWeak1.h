//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesWeak2;
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesWeak1
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::weak_ptr<CCyclicReferencesWeak2>					MPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MPointer.use_count());
		}

		std::shared_ptr<CCyclicReferencesWeak2> GetPointer(void)
		{
			return(MPointer.lock());
		}

		void SetPointer(std::weak_ptr<CCyclicReferencesWeak2> Pointer)
		{
			MPointer=Pointer;
		}

		void SomeMethod(void)
		{
			std::wcout << L"METHOD CCyclicReferencesWeak1::SomeMethod() CALLED !" << std::endl;
		}

		void CallOther(void);

	public:
		~CCyclicReferencesWeak1(void)
		{
			std::wcout << L"METHOD CCyclicReferencesWeak1::~CCyclicReferencesWeak1() CALLED ! REFERENCE COUNTER [" << MPointer.use_count() << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------