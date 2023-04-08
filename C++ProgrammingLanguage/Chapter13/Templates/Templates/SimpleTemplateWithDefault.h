//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva DEFUALT hodnotu TEMPLATE PARAMETRU.
template<typename TVariable=double>
class CSimpleTemplateWithDefault
{
	private:
		TVariable												MVariable;

	public:
		const TVariable& GetVariable(void) const;

	public:
		CSimpleTemplateWithDefault(TVariable Variable);
		virtual ~CSimpleTemplateWithDefault(void);
};
//-------------------------------------------------------------------------------------------------------