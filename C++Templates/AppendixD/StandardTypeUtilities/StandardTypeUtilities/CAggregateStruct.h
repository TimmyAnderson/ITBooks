//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
struct CAggregateStruct final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		int														MValue1;
		int														MValue2;

	public:
		int GetValue1(void) const noexcept;
		int GetValue2(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------