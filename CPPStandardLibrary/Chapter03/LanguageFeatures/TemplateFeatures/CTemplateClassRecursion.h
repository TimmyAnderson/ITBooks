//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Toto je ITERATION STEP TEMPLATE ITERATION.
template<int IterationStep>
class CTemplateClassRecursion
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Tu sa vykonava COMPILE TIME RECURSION, pretoze sa vola TEMPLATE s (IterationStep-1).
		static const int										VALUE=IterationStep+CTemplateClassRecursion<IterationStep-1>::VALUE;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Toto je TERMINAL STEP TEMPLATE ITERATION.
// !!! Jedna sa o TEMPLATE SPECIALIZATION.
template<>
class CTemplateClassRecursion<1>
{
//-------------------------------------------------------------------------------------------------------
	public:
		// !!! Tu sa vracia VALUE pre hodnotu ak je 'IterationStep' rovny 1.
		static const int										VALUE=1;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------