//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! Toto je jeden zo sposobov vyuzitia KEYWORD 'typename'.
template<typename TType> 
class CTypenameTemplate
{
	public:
		// Definujem INTERNE TYPY.
		typedef TType											CValueType;
		typedef TType*											CPointerType;

	private:
		TType													MValue;

	public:
		TType GetValue(void) const;

	public:
		CTypenameTemplate(TType Value);
		virtual ~CTypenameTemplate(void);
};
//-------------------------------------------------------------------------------------------------------