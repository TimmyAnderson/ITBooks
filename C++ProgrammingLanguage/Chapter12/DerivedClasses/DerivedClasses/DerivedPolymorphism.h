//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "BasePolymorphism.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedPolymorphism : public CBasePolymorphism
{
	private:
		std::wstring											MDerivedText;

	public:
		virtual void Print(void);

	public:
		const std::wstring& GetDerivedText(void) const;

	public:
		CDerivedPolymorphism(std::wstring BaseText1, std::wstring BaseText2, std::wstring DerivedText);
		virtual ~CDerivedPolymorphism(void);
};
//-------------------------------------------------------------------------------------------------------