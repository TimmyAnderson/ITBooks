//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
class CPerfectForwardingInConstructorNoTemplate final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		explicit CPerfectForwardingInConstructorNoTemplate(const std::wstring& Value);
		explicit CPerfectForwardingInConstructorNoTemplate(std::wstring&& Value);
		CPerfectForwardingInConstructorNoTemplate(const CPerfectForwardingInConstructorNoTemplate& Value);
		CPerfectForwardingInConstructorNoTemplate(CPerfectForwardingInConstructorNoTemplate&& Value) noexcept;
		virtual ~CPerfectForwardingInConstructorNoTemplate(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------