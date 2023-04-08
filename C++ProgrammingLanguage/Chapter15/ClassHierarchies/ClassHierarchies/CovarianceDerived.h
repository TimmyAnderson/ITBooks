//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CovarianceBase.h"
#include "DummyDerived.h"
//-------------------------------------------------------------------------------------------------------
class CCovarianceDerived : public CCovarianceBase
{
	private:
		static CDummyDerived									MDummyDerived;
		static CCovarianceDerived								MCovarianceDerived;

	public:
		// !!!!! COVARIANCE znamena, ze OVERRIDED metoda moze NAMIESTO CDummyBase*, ktoru vracia metoda v BASE CLASS ZDEDENU CLASS CDummyDerived*.
		CDummyDerived* GetDummy(void);
		// !!!!! COVARIANCE znamena, ze OVERRIDED metoda moze NAMIESTO CCovarianceBase*, ktoru vracia metoda v BASE CLASS ZDEDENU CLASS CCovarianceDerived*.
		CCovarianceDerived* GetCovariance(void);

	public:
		virtual void PrintText(void);

	public:
		CCovarianceDerived(void);
		virtual ~CCovarianceDerived(void);
};
//-------------------------------------------------------------------------------------------------------