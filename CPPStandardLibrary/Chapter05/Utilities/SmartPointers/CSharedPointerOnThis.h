//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
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
			std::wcout << L"METHOD CSharedPointerOnThis::SomeMethod() CALLED !" << std::endl;
		}

	public:
		~CSharedPointerOnThis(void)
		{
			std::wcout << L"METHOD CSharedPointerOnThis::~CSharedPointerOnThis() CALLED ! REFERENCE COUNTER [" << MThisPointer.use_count() << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------