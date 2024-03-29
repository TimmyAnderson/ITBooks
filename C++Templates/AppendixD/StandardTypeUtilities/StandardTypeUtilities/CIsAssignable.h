//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CIsAssignable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CNonTrivialType											MField;

	public:
		CIsAssignable& operator=(const CNonTrivialType& Other);

	public:
		const CNonTrivialType& GetField(void) const;
		void SetField(const CNonTrivialType& Field);

	public:
		void SomeMethod(void);

	public:
		CIsAssignable(int Value1, double Value2);
		~CIsAssignable(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------