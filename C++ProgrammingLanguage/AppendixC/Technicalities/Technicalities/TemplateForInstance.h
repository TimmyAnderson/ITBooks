//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class CTemplateForInstance
{
	private:
		TType													MField;

	public:
		TType GetValue(void);

	public:
		CTemplateForInstance(TType Field);
		virtual ~CTemplateForInstance(void);
};
//-------------------------------------------------------------------------------------------------------