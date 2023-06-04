//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
class COverloadResolutionForThis final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		operator wchar_t*(void);
		operator wchar_t const*(void) const;

	public:
		wchar_t& operator[](std::size_t Index);
		const wchar_t& operator[](std::size_t Index) const;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		COverloadResolutionForThis(const wchar_t* Value);
		virtual ~COverloadResolutionForThis(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------