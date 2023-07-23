//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CNonIsAssignable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CNonTrivialType											MField;

	public:
		const CNonTrivialType& GetField(void) const;
		void SetField(const CNonTrivialType& Field);

	public:
		void SomeMethod(void);

	public:
		CNonIsAssignable(int Value1, double Value2);
		~CNonIsAssignable(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------