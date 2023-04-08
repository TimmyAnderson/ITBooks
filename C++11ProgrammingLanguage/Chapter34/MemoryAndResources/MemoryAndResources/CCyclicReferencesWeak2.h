//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
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
			wprintf_s(L"METHOD CCyclicReferencesWeak2::SomeMethod() CALLED !\n");
		}

		void CallOther(void);

	public:
		~CCyclicReferencesWeak2(void)
		{
			wprintf_s(L"METHOD CCyclicReferencesWeak2::~CCyclicReferencesWeak2() CALLED ! REFERENCE COUNTER [%d] !\n",MPointer.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------