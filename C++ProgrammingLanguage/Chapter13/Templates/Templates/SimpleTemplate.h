//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TVariable>
class CSimpleTemplate
{
	private:
		TVariable												MVariable;

	public:
		const TVariable& GetVariable(void) const;

	public:
		CSimpleTemplate(TVariable Variable);
		virtual ~CSimpleTemplate(void);
};
//-------------------------------------------------------------------------------------------------------