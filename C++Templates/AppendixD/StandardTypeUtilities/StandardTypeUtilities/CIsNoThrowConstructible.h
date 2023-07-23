//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CIsNoThrowConstructible final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		double													MField2;
		CNonTrivialType											MField3;

	public:
		int GetField1(void) const;
		double GetField2(void) const;
		const CNonTrivialType& GetField3(void) const;
		void SetField1(int Field1);
		void SetField2(double Field2);
		void SetField3(const CNonTrivialType& Field3);

	public:
		void SomeMethod(void);

	public:
		CIsNoThrowConstructible(int Field1);
		CIsNoThrowConstructible(int Field1, double Field2) noexcept;
		~CIsNoThrowConstructible(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------