//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CIsNoThrowAssignable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CNonTrivialType											MField;

	public:
		CIsNoThrowAssignable& operator=(const CNonTrivialType& Other) noexcept;

	public:
		const CNonTrivialType& GetField(void) const;
		void SetField(const CNonTrivialType& Field);

	public:
		void SomeMethod(void);

	public:
		CIsNoThrowAssignable(int Value1, double Value2);
		~CIsNoThrowAssignable(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------