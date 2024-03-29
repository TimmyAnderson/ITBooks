//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CTypeWithMYTYPEMembers final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													MY_TYPE_1=int;
		using													MY_TYPE_2=double;

	private:
		MY_TYPE_1												MValue1;
		MY_TYPE_2												MValue2;

	public:
		MY_TYPE_1 GetValue1(void) const noexcept;
		MY_TYPE_2 GetValue2(void) const noexcept;

	public:
		CTypeWithMYTYPEMembers(MY_TYPE_1 Value1, MY_TYPE_2 Value2);
		virtual ~CTypeWithMYTYPEMembers(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------