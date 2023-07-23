//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CNonIsTriviallyAssignable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MField;

	public:
		CNonIsTriviallyAssignable& operator=(const CNonIsTriviallyAssignable& Other)=delete;
		CNonIsTriviallyAssignable& operator=(CNonIsTriviallyAssignable&& Other)=delete;

	public:
		int GetField(void) const;
		void SetField(int Field);

	public:
		void SomeMethod(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------