//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CConversionSequenceBase.h"
//----------------------------------------------------------------------------------------------------------------------
class CConversionSequenceDerived final : public CConversionSequenceBase
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		CConversionSequenceDerived(int Value);
		virtual ~CConversionSequenceDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------