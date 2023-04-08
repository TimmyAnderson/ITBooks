//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesShared1;
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesShared2
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CCyclicReferencesShared1>				MPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MPointer.use_count());
		}

		std::shared_ptr<CCyclicReferencesShared1>& GetPointer(void)
		{
			return(MPointer);
		}

		void SetPointer(std::shared_ptr<CCyclicReferencesShared1>& Pointer)
		{
			MPointer=Pointer;
		}

		void SomeMethod(void)
		{
			wprintf_s(L"METHOD CCyclicReferencesShared2::SomeMethod() CALLED !\n");
		}

		void CallOther(void);

	public:
		~CCyclicReferencesShared2(void)
		{
			wprintf_s(L"METHOD CCyclicReferencesShared2::~CCyclicReferencesShared2() CALLED ! REFERENCE COUNTER [%d] !\n",MPointer.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------