//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
class CVariadicClassOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! INNER TEMPLATE CLASS moze pouzit TEMPLATE PACK na definovanie TEMPLATE NON-TYPE PARAMETERS.
		template<TTypes... VALUES>
		class CVariadicClassInner;

	public:
		CVariadicClassOuter(void);
		virtual ~CVariadicClassOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariadicClassOuter<TTypes...>::CVariadicClassOuter(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariadicClassOuter<TTypes...>::~CVariadicClassOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! INNER TEMPLATE CLASS moze pouzit TEMPLATE PACK na definovanie TEMPLATE NON-TYPE PARAMETERS.
template<typename... TTypes>
template<TTypes... VALUES>
class CVariadicClassOuter<TTypes...>::CVariadicClassInner final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		template<typename TLocalType, typename... TLocalTypes>
		void InternalPrint(size_t Index, TLocalType Value, TLocalTypes... Values)
		{
			std::wcout << "INNER CLASS - INDEX [" << Index << L"] TYPE [" << GetTypeInfoName<TLocalType>() << "] VALUE [" << Value << L"]." << std::endl;

			if constexpr (sizeof...(Values)>0)
			{
				InternalPrint((Index+1),Values...);
			}
		}

	public:
		void Print(void)
		{
			InternalPrint(1,VALUES...);
		}

	public:
		CVariadicClassInner(void)
		{
		}

		virtual ~CVariadicClassInner(void) noexcept
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------