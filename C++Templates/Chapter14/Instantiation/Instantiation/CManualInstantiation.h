//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!!!! HEADER FILE obsahuje iba DECLARATIONS C++ CLASS METHODS, ale NIE ich DEFINITIONS. Tym padom C++ NEMOZE v kazdej TRANSLATION UNIT do ktorej je tento HEADER FILE vlozeny vytvorit BINARY CODE pre TEMPLATE METHODS, kedze nema ich DEFINITIONS.
template<typename TType>
class CManualInstantiation final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		const TType& GetValue(void) const noexcept;

	public:
		CManualInstantiation(const TType& Value);
		virtual ~CManualInstantiation(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! HEADER FILE obsahuje iba DECLARATIONS C++ FUNCTION, ale NIE jej DEFINITION. Tym padom C++ NEMOZE v kazdej TRANSLATION UNIT do ktorej je tento HEADER FILE vlozeny vytvorit BINARY CODE pre TEMPLATE FUNCTION, kedze nema jej DEFINITION.
template<typename TType>
void ManualInstantiationFunction(const TType& Value);
//----------------------------------------------------------------------------------------------------------------------