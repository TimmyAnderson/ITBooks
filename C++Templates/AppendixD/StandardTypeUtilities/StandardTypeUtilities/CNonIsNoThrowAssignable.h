//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CNonIsNoThrowAssignable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CNonTrivialType											MField;

	public:
		CNonIsNoThrowAssignable& operator=(const CNonTrivialType& Other);

	public:
		const CNonTrivialType& GetField(void) const;
		void SetField(const CNonTrivialType& Field);

	public:
		void SomeMethod(void);

	public:
		CNonIsNoThrowAssignable(int Value1, double Value2);
		~CNonIsNoThrowAssignable(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------