//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CValueNoConstructors final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		CValueNoConstructors& operator=(const CValueNoConstructors& Other)=delete;
		CValueNoConstructors& operator=(CValueNoConstructors&& Other) noexcept=delete;

	public:
		int GetValue(void) const noexcept;

	public:
		CValueNoConstructors(void);
		CValueNoConstructors(int Value);
		CValueNoConstructors(const CValueNoConstructors& Other)=delete;
		CValueNoConstructors(CValueNoConstructors&& Other) noexcept=delete;
		~CValueNoConstructors(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------