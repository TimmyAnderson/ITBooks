//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CStructuredBindingCArrayValue final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const CStructuredBindingCArrayValue& Value);

	private:
		int														MValue;

	public:
		CStructuredBindingCArrayValue& operator=(const CStructuredBindingCArrayValue& Other);
		CStructuredBindingCArrayValue& operator=(CStructuredBindingCArrayValue&& Other) noexcept;

	public:
		int GetValue(void) const noexcept;
		void SetValue(int Value) noexcept;

	public:
		CStructuredBindingCArrayValue(void);
		CStructuredBindingCArrayValue(int Value);
		CStructuredBindingCArrayValue(const CStructuredBindingCArrayValue& Other);
		CStructuredBindingCArrayValue(CStructuredBindingCArrayValue&& Other) noexcept;
		virtual ~CStructuredBindingCArrayValue(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------