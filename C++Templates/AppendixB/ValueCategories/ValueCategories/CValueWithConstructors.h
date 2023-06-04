//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CValueWithConstructors final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CValueWithConstructors& operator=(const CValueWithConstructors& Other);
		CValueWithConstructors& operator=(CValueWithConstructors&& Other) noexcept;

	public:
		int GetValue(void) const noexcept;

	public:
		CValueWithConstructors(void);
		CValueWithConstructors(int Value);
		CValueWithConstructors(const CValueWithConstructors& Other);
		CValueWithConstructors(CValueWithConstructors&& Other) noexcept;
		~CValueWithConstructors(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------