//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CNonIsNoThrowSwappableWith final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField1;
		double													MField2;

	public:
		int GetField1(void) const;
		double GetField2(void) const;
		void SetField1(int Field1);
		void SetField2(double Field2);

	public:
		void SomeMethod(void);

	public:
		CNonIsNoThrowSwappableWith(int Field1, double Field2);
		~CNonIsNoThrowSwappableWith(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION NIE JE OZNACENA KEYWORD [noexcept].
void swap(CNonIsNoThrowSwappableWith& Value1, CNonIsNoThrowSwappableWith& Value2);
//----------------------------------------------------------------------------------------------------------------------