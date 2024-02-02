//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CCRTPAndRestrictedTemplateExpansionBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCRTPAndRestrictedTemplateExpansionDerived final : public CCRTPAndRestrictedTemplateExpansionBase<CCRTPAndRestrictedTemplateExpansionDerived>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		friend bool operator==(const CCRTPAndRestrictedTemplateExpansionDerived& Value1, const CCRTPAndRestrictedTemplateExpansionDerived& Value2)
		{
			bool												Result=(Value1.MValue==Value2.MValue);

			return(Result);
		}

	public:
		int GetValue(void) const noexcept;

	public:
		CCRTPAndRestrictedTemplateExpansionDerived(int Value);
		virtual ~CCRTPAndRestrictedTemplateExpansionDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------