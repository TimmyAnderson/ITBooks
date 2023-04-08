//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <utility>
//-----------------------------------------------------------------------------
struct SError
{
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename TLocalType>
auto CheckIfHasMethodXXX(TLocalType Value) -> decltype(Value.XXX())
{
	// !!! Kvoli COMPILERU, aby nehlasil WARNING.
	(void)Value;

	return(true);
}
//-----------------------------------------------------------------------------
template <typename... TTypes>
SError CheckIfHasMethodXXX(TTypes...)
{
	SError														Error;

	return(Error);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
struct STestFunctionXXX
{
//-----------------------------------------------------------------------------
	public:
		static const bool										RESULT=true;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<>
struct STestFunctionXXX<SError>
{
//-----------------------------------------------------------------------------
	public:
		static const bool										RESULT=false;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! TEMPLATE sa pouziva na rozlisenie ci vo FIELD [RESULT] bude hodnota TRUE, alebo FALSE.
// !!!!! Kedze C++ NEUMOZNUJE deklarovat 2 TEMPLATES s ROVNAKYM MENOM (ako je to v pripade FUNCTIONS) je NUTNE pouzit INHERITANCE.
// !!!!! Ak sa TEMPLATE [SCheckFunctionXXX] pouzije pre TYPES, ktore MAJU METHOD XXX(), tak CheckIfHasMethodXXX() vrati RETURN VALUE TYPE [bool]. Konkretny TYPE NIE JE DOLEZITY. DOLEZITE je iba to, ze je to ROZNY TYPE ako [SError]. Kedze CheckIfHasMethodXXX() vratila RETURN VALUE TYPE [bool], C++ pouzije TEMPLATE [SCheckFunctionXXX], ktora do FIELD [RESULT] uklada hodnotu TRUE.
// !!!!! Ak sa TEMPLATE [SCheckFunctionXXX] pouzije pre TYPES, ktore NEMAJU METHOD XXX(), tak CheckIfHasMethodXXX() vrati RETURN VALUE TYPE [SError]. Kedze CheckIfHasMethodXXX() vratila RETURN VALUE TYPE [bool], C++ pouzije TEMPLATE SPECIALIZATION pre TYPE [SError], ktora do FIELD [RESULT] uklada hodnotu FALSE.
template<typename TType>
struct SCheckFunctionXXX : public STestFunctionXXX<decltype(CheckIfHasMethodXXX(std::declval<TType>()))>
{
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------