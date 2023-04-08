//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE obsahuje ako TEMPLATE PARAMETER inu TEMPLATE.
// !!!!! Visual C++ toto NEDOKAZE SKOMPILOVAT. Namiesto posledneho 'typename' MUSI BYT 'class', inak to Visual C++ NEDOKAZE SKOMPILOVAT.
//template <typename TType, template<typename TType> typename TTemplate>
// !!!!! Toto C++ KOMPILUJE BEZ PROBLEMOV.
template <typename TType, template<typename TType> class TTemplate>
class CTemplateWithTemplateAsParameter
{
	private:
		// !!!!! Pouzitie TEMPLATE PARAMETERU.
		TTemplate<TType>										MTemplateValues;
		TTemplate<TType*>										MTemplatePointers;

	public:
		TTemplate<TType> GetTemplateValues(void);
		TTemplate<TType*> GetTemplatePointers(void);
		void SetTemplateValues(TTemplate<TType> Param);
		void SetTemplatePointers(TTemplate<TType*> Param);

	public:
		CTemplateWithTemplateAsParameter(void);
		virtual ~CTemplateWithTemplateAsParameter(void);
};
//-------------------------------------------------------------------------------------------------------