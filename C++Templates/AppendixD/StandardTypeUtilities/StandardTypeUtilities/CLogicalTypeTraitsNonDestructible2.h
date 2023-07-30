//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CLogicalTypeTraitsNonDestructible2
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
		CLogicalTypeTraitsNonDestructible2(int Field1, double Field2);
		~CLogicalTypeTraitsNonDestructible2(void)=delete;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------