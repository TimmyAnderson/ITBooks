//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CIsConvertible final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const;
		void SetField(int Field);

	public:
		void SomeMethod(void);

	public:
		CIsConvertible(int Field);
		~CIsConvertible(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------