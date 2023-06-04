//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CClassWithOperatorLowerAndMultipleException final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		// !!! OPERATORS NIE SU oznacene pomocou KEYWORD [noexcept].
		bool operator<(const CClassWithOperatorLowerAndMultipleException& Other) const;
		CClassWithOperatorLowerAndMultipleException& operator*(const CClassWithOperatorLowerAndMultipleException& Other);

	public:
		int GetValue(void) const noexcept;

	public:
		CClassWithOperatorLowerAndMultipleException(void);
		CClassWithOperatorLowerAndMultipleException(int Value);
		virtual ~CClassWithOperatorLowerAndMultipleException(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------