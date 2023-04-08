//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
class CTemplateAsQualifier
{
	public:
		template<typename TType> TType* Allocate(void);
		template<typename TType> void Delocate(TType* Object);

	public:
		CTemplateAsQualifier(void);
		virtual ~CTemplateAsQualifier(void);
};
//-------------------------------------------------------------------------------------------------------