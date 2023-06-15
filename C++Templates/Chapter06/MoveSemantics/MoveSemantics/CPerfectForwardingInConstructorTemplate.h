//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
class CPerfectForwardingInConstructorTemplate final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		// !!!!! PERFECT FORWARDING CONSTRUCTOR.
		template<typename TType>
		explicit CPerfectForwardingInConstructorTemplate(TType&& Value);
		CPerfectForwardingInConstructorTemplate(const CPerfectForwardingInConstructorTemplate& Value);
		CPerfectForwardingInConstructorTemplate(CPerfectForwardingInConstructorTemplate&& Value) noexcept;
		virtual ~CPerfectForwardingInConstructorTemplate(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PERFECT FORWARDING CONSTRUCTOR.
template<typename TType>
CPerfectForwardingInConstructorTemplate::CPerfectForwardingInConstructorTemplate(TType&& Value)
	: MValue(std::forward<TType>(Value))
{
	std::wcout << L"TEMPLATE - FORWARDING CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------