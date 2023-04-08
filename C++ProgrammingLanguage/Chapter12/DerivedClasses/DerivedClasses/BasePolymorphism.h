//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBasePolymorphism
{
	private:
		std::wstring											MBaseText1;
		std::wstring											MBaseText2;

	public:
		virtual void Print(void);

	public:
		const std::wstring& GetBaseText1(void) const;
		const std::wstring& GetBaseText2(void) const;

	public:
		CBasePolymorphism(std::wstring BaseText1, std::wstring BaseText2);
		virtual ~CBasePolymorphism(void);
};
//-------------------------------------------------------------------------------------------------------