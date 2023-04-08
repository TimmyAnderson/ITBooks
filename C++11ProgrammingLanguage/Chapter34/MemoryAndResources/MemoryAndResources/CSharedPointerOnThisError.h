//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
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
			wprintf_s(L"METHOD CSharedPointerOnThisError::SomeMethod() CALLED !\n");
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
			wprintf_s(L"METHOD CSharedPointerOnThisError::~CSharedPointerOnThis() CALLED ! REFERENCE COUNTER [%d] !\n",MThisPointer.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------