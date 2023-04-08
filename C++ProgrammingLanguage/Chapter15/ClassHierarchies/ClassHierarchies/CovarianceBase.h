//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "DummyBase.h"
//-------------------------------------------------------------------------------------------------------
class CCovarianceBase
{
	private:
		static CDummyBase										MDummyBase;
		static CCovarianceBase									MCovarianceBase;

	public:
		virtual void PrintText(void);

	public:
		CDummyBase* GetDummy(void);
		CCovarianceBase* GetCovariance(void);

	public:
		CCovarianceBase(void);
		virtual ~CCovarianceBase(void);
};
//-------------------------------------------------------------------------------------------------------