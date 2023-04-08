//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TVariable, int INT>
class CSimpleTemplateWithInt
{
	private:
		TVariable												MVariable;

	public:
		const TVariable& GetVariable(void) const;
		void PrintINTParameter(void) const;

	public:
		CSimpleTemplateWithInt(TVariable Variable);
		virtual ~CSimpleTemplateWithInt(void);
};
//-------------------------------------------------------------------------------------------------------