//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
class CPerfectForwardingInConstructorTemplateEnableIf final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		// !!!!! PERFECT FORWARDING CONSTRUCTOR.
		// !!!!! Pomocou TYPE TRAIT [enable_if<>] je povoleny iba ak TYPE 'TType' je konvertovatelny na TYPE [wstring]. Vdaka tomu C++ spravne zavola COPY CONSTRUCTOR, ak dostane CONSTRUCTOR ako PARAMETER TYPE [const CPerfectForwardingInConstructorTemplateEnableIf&].
		template<typename TType,typename=std::enable_if<std::is_convertible<TType,std::wstring>::value>::type>
		explicit CPerfectForwardingInConstructorTemplateEnableIf(TType&& Value);
		CPerfectForwardingInConstructorTemplateEnableIf(const CPerfectForwardingInConstructorTemplateEnableIf& Value);
		CPerfectForwardingInConstructorTemplateEnableIf(CPerfectForwardingInConstructorTemplateEnableIf&& Value) noexcept;
		virtual ~CPerfectForwardingInConstructorTemplateEnableIf(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PERFECT FORWARDING CONSTRUCTOR.
// !!!!! Tu uz NESMIE byt DEFINITION DEFAULT VALUE pre TEMPLATE PARAMETERS, pretoze sa nachadza v DECLARATION METHOD.
template<typename TType,typename>
CPerfectForwardingInConstructorTemplateEnableIf::CPerfectForwardingInConstructorTemplateEnableIf(TType&& Value)
	: MValue(std::forward<TType>(Value))
{
	std::wcout << L"TEMPLATE - FORWARDING CONSTRUCTOR CALLED with VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------