//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateClassInheritanceBase.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! C++ umoznuje aby DERIVED CLASS mala ako BASE CLASS rovnaku TEMPLATE CLASS, ak sa TEMPLATE ARGUMENTS vsetkych TEMPLATE CLASSES rovnakeho TYPE vzajomne lisia.
class CTemplateClassInheritanceDerived final : public CTemplateClassInheritanceBase<int,1>, public CTemplateClassInheritanceBase<int,2>, public CTemplateClassInheritanceBase<double,1>, public CTemplateClassInheritanceBase<double,2>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void DoSomething(void) const;

	public:
		CTemplateClassInheritanceDerived(void);
		virtual ~CTemplateClassInheritanceDerived(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------