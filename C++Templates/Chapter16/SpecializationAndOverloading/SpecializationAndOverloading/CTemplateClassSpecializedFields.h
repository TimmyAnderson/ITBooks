//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
struct STemplateClassSpecializedFields final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const STemplateClassSpecializedFields& Value);

	private:
		int														MField;

	public:
		int GetField(void) const noexcept;
		void SetField(int Value) noexcept;

	public:
		STemplateClassSpecializedFields(int Value);
		STemplateClassSpecializedFields(const STemplateClassSpecializedFields&)=delete;
		virtual ~STemplateClassSpecializedFields(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateClassSpecializedFields final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! Tento CODE je IN-CLASS DECLARATION TEMPLATE CLASS STATIC FIELD.
		static TType											MStaticField;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tento CODE je OUT-OF-CLASS DECLARATION TEMPLATE CLASS STATIC FIELD SPECIALIZATION.
template<>
STemplateClassSpecializedFields									CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
inline void TemplateClassSpecializedFieldsTest(void)
{
	std::wcout << L"TEMPLATE CLASS STATIC FIELD SPECIALIZATION <STemplateClassSpecializedFields> - TYPE [" << GetTypeInfoName<decltype(CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField)>() << L"] STATIC FIELD [" << CTemplateClassSpecializedFields<STemplateClassSpecializedFields>::MStaticField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------