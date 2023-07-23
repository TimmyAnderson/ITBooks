//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CNonTrivialType.h"
//----------------------------------------------------------------------------------------------------------------------
class CIsMoveConstructible1 final
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
		CIsMoveConstructible1(int Field1, double Field2);
		CIsMoveConstructible1(CIsMoveConstructible1&& Other);
		~CIsMoveConstructible1(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------