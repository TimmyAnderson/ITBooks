//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesWeak1;
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesWeak2
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::weak_ptr<CCyclicReferencesWeak1>					MPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MPointer.use_count());
		}

		std::shared_ptr<CCyclicReferencesWeak1> GetPointer(void)
		{
			return(MPointer.lock());
		}

		void SetPointer(std::weak_ptr<CCyclicReferencesWeak1> Pointer)
		{
			MPointer=Pointer;
		}

		void SomeMethod(void)
		{
			std::wcout << L"METHOD CCyclicReferencesWeak2::SomeMethod() CALLED !" << std::endl;
		}

		void CallOther(void);

	public:
		~CCyclicReferencesWeak2(void)
		{
			std::wcout << L"METHOD CCyclicReferencesWeak2::~CCyclicReferencesWeak2() CALLED ! REFERENCE COUNTER [" << MPointer.use_count() << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------