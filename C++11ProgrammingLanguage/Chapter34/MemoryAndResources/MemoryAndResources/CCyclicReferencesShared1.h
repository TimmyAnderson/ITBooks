//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesShared2;
//-------------------------------------------------------------------------------------------------------
class CCyclicReferencesShared1
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CCyclicReferencesShared2>				MPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MPointer.use_count());
		}

		std::shared_ptr<CCyclicReferencesShared2>& GetPointer(void)
		{
			return(MPointer);
		}

		void SetPointer(std::shared_ptr<CCyclicReferencesShared2>& Pointer)
		{
			MPointer=Pointer;
		}

		void SomeMethod(void)
		{
			wprintf_s(L"METHOD CCyclicReferencesShared1::SomeMethod() CALLED !\n");
		}

		void CallOther(void);

	public:
		~CCyclicReferencesShared1(void)
		{
			wprintf_s(L"METHOD CCyclicReferencesShared1::~CCyclicReferencesShared1() CALLED ! REFERENCE COUNTER [%d] !\n",MPointer.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------