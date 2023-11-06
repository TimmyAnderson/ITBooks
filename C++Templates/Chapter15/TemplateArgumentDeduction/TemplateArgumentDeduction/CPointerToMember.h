//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CPointerToMember final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int GetValue(void) const noexcept;

	public:
		CPointerToMember(int Value);
		virtual ~CPointerToMember(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------