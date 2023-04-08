//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
// !!! CLASS MUSI byt DERIVED z CLASS [enable_shared_from_this<T>].
class CSharedPointerOnThisError : public std::enable_shared_from_this<CSharedPointerOnThisError>
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CSharedPointerOnThisError>				MThisPointer;

	public:
		long GetPointerReferenceCounter(void)
		{
			return(MThisPointer.use_count());
		}

		std::shared_ptr<CSharedPointerOnThisError>& GetPointer(void)
		{
			return(MThisPointer);
		}

		void SomeMethod(void)
		{
			std::wcout << L"METHOD CSharedPointerOnThisError::SomeMethod() CALLED !" << std::endl;
		}

	public:
		CSharedPointerOnThisError(void)
		{
			// !!! Zavola sa METHOD enabled_shared_from_this<T>.shared_from_this().
			// !!!!! Sposobi RUNTIME ERROR, pretoze v CONSTRUCTORS NIE JE MOZNE volat METHOD shared_from_this().
			MThisPointer=shared_from_this();
		}

		~CSharedPointerOnThisError(void)
		{
			std::wcout << L"METHOD CSharedPointerOnThisError::~CSharedPointerOnThis() CALLED ! REFERENCE COUNTER [" << MThisPointer.use_count() << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------