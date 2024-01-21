//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CInstantiationSafeTemplatesTypesBoolConvertibleImplicit final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MValue;

	public:
		operator bool(void) const;

	public:
		bool GetValue(void) const noexcept;

	public:
		CInstantiationSafeTemplatesTypesBoolConvertibleImplicit(bool Value);
		virtual ~CInstantiationSafeTemplatesTypesBoolConvertibleImplicit(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------