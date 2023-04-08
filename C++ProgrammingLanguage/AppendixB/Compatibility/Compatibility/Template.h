//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template <typename TClassType>
class CTemplate
{
	private:
		TClassType												MValue;

	public:
		TClassType GetValue(void);

	public:
		// !!!!! TEMPLATE FUNCTION definovana v TEMPLATE CLASS. Visual C++ toto PODPORUJE.
		template<typename TFunctionType>
		TFunctionType GetValues(TFunctionType InValue, TClassType* OutValue);

	public:
		CTemplate(TClassType MValue);
		virtual ~CTemplate(void);
};
//-------------------------------------------------------------------------------------------------------