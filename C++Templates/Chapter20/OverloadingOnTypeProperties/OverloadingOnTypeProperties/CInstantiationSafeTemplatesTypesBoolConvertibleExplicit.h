//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
class CInstantiationSafeTemplatesTypesBoolConvertibleExplicit final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MValue;

	public:
		explicit operator bool(void) const;

	public:
		bool GetValue(void) const noexcept;

	public:
		CInstantiationSafeTemplatesTypesBoolConvertibleExplicit(bool Value);
		virtual ~CInstantiationSafeTemplatesTypesBoolConvertibleExplicit(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------