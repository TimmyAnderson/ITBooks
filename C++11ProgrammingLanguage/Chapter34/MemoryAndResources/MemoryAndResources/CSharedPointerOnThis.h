//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
// !!! CLASS MUSI byt DERIVED z CLASS [enabled_shared_from_this<T>].
class CSharedPointerOnThis : public std::enable_shared_from_this<CSharedPointerOnThis>
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CSharedPointerOnThis>					MThisPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MThisPointer.use_count());
		}

		std::shared_ptr<CSharedPointerOnThis>& GetPointer(void)
		{
			return(MThisPointer);
		}

		void SetPointer(void)
		{
			// !!! Zavola sa METHOD enabled_shared_from_this<T>.shared_from_this().
			MThisPointer=shared_from_this();
		}

		void ResetPointer(void)
		{
			MThisPointer=nullptr;
		}

		void SomeMethod(void)
		{
			wprintf_s(L"METHOD CSharedPointerOnThis::SomeMethod() CALLED !\n");
		}

	public:
		~CSharedPointerOnThis(void)
		{
			wprintf_s(L"METHOD CSharedPointerOnThis::~CSharedPointerOnThis() CALLED ! REFERENCE COUNTER [%d] !\n",MThisPointer.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------