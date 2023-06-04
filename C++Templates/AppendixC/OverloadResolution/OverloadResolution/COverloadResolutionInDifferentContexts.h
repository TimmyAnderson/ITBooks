//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
class COverloadResolutionInDifferentContexts final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		long													MValue1;
		double													MValue2;
		std::wstring											MValue3;

	public:
		operator long(void) const;
		operator double(void) const;

	public:
		long GetValue1(void) const noexcept;
		double GetValue2(void) const noexcept;
		const std::wstring& GetValue3(void) const noexcept;

	public:
		COverloadResolutionInDifferentContexts(long Value);
		COverloadResolutionInDifferentContexts(double Value);
		COverloadResolutionInDifferentContexts(const std::wstring& Value);
		virtual ~COverloadResolutionInDifferentContexts(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------