//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CClassWithOperatorLowerAndMultiple final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		using													TInnerType=int;

	public:
		bool operator<(const CClassWithOperatorLowerAndMultiple& Other) const noexcept;
		CClassWithOperatorLowerAndMultiple& operator*(const CClassWithOperatorLowerAndMultiple& Other) noexcept;

	public:
		int GetValue(void) const noexcept;

	public:
		CClassWithOperatorLowerAndMultiple(void);
		CClassWithOperatorLowerAndMultiple(int Value);
		virtual ~CClassWithOperatorLowerAndMultiple(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------