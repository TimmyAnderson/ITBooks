//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! ADDITIONAL CLASS sluziaca na rozsirenie MIXIN CLASS. CLASS NIE je DERIVED z MIXIN CLASS.
// !!!!! ADDITIONAL CLASS v MIXIN PATTERN predstavuje BASE CLASS, ktoru dedi MIXIN (DERIVED) CLASS.
class CMixinClassMixinsAdditionalData2
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		double													MValueDouble;

	public:
		double GetValueDouble(void) const;
		void SetValueDouble(double Value);

	public:
		CMixinClassMixinsAdditionalData2(void);
		virtual ~CMixinClassMixinsAdditionalData2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------