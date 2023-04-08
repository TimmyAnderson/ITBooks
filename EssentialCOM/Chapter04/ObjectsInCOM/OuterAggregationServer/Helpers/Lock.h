//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include "CriticalSectionWrapper.h"
//------------------------------------------------------------------------------------------------------
class CLock
{
	private:
		CCriticalSectionWrapper&								MCriticalSectionWrapper;

	public:
		CLock(CCriticalSectionWrapper& CriticalSectionWrapper);
		~CLock(void);
};
//------------------------------------------------------------------------------------------------------