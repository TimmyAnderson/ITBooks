//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
class CNonFriendFunctionClass final
{
//----------------------------------------------------------------------------------------------------------------------
	friend std::wostream& operator<<(std::wostream& Stream, const CNonFriendFunctionClass& Value);

	public:
		/*
		// !!!!! FRIEND FUNCTION bude viditelna aj na PARENT SCOPE, co je v tomto pripade NAMESPACE SCOPE.
		// !!!!! FRIEND FUNCTION vsak MUSI mat aspon 1 FUNCTION PARAMETER TYPE TEMPLATE CLASS [CNonFriendFunctionClass<TType>], aby vdaka ARGUMENT DEPENDENT LOOKUP bola v NAMESPACE SCOPE viditelna.
		friend void RestrictedTemplateExpansionFriendFunction(const CNonFriendFunctionClass& Value)
		{
			std::wcout << L"NON FRIEND FUNCTION CLASS - FRIEND FUNCTION - VALUE [" << Value.MField << L"]." << std::endl;
		}
		*/

	private:
		std::wstring											MField;

	public:
		const std::wstring& GetField(void) const noexcept;

	public:
		CNonFriendFunctionClass(void);
		CNonFriendFunctionClass(const wchar_t* Field);
		CNonFriendFunctionClass(const std::wstring& Field);
		virtual ~CNonFriendFunctionClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------