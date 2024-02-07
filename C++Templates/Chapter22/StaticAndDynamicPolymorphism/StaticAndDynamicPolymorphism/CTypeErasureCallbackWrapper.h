//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <utility>
#include "CTypeErasureCallbackWrapperBridgeInterface.h"
#include "CTypeErasureCallbackWrapperBridgeImplementation.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS umoznuje ukladat CALLBACK CODE ako POINTER na FUNCTION, LAMBDA FUNCTION ci FUNCTION OBJECT.
// !!!!! DECLARATION PRIMARY TEMPLATE CLASS.
template<typename TSignature>
class CTypeErasureCallbackWrapper;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DEFINITION TEMPLATE CLASS SPECIALIZATION.
// !!! CLASS implementuje TYPE ERASURE PATTERN pre rozlicne CALLBACK TYPES ako su POINTER na FUNCTION, REFERENCE na FUNCTION, LAMBDA EXPRESSION ci vsetky FUNCTION OBJECTS.
// !!!!! Cielom implementacie TYPE ERASURE PATTERN aby tato pomerne rozsiahla TEMPLATE CLASS nebola INSTANTIATED pre KAZDY CALLBACK TYPE, pretoze to by znamenalo generovanie velkeho mnozstva BINARY CODE.
// !!!!! CLASS NEMA ako TEMPLATE PARAMETER CALLBACK TYPE. Vdaka tomu NIE JE INSTANTIATED pre KAZDY CALLBACK TYPE.
// !!!!! CALLBACK TYPE je uchovany a pozivany cez FIELD na INTERFACE TYPE. Kedze ani tento INTERFACE TYPE neobsahuje ako TEMPLATE PARAMETER CALLBACK TYPE, tak ani ten nie je INSTANTIATED pre KAZDY CALLBACK TYPE.
template<typename TReturnValue, typename... TParameters>
class CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		friend bool operator==(const CTypeErasureCallbackWrapper& Function1, const CTypeErasureCallbackWrapper& Function2)
		{
			if (!Function1 || !Function2)
			{
				bool											Result=(!Function1 && !Function2);

				return(Result);
			}
			else
			{
				// !!!!! Vola sa VIRTUAL METHOD INTERFACE CLASS, ktora vykona porovnanie instancii TYPES.
				// !!!!! TEMPLATE CLASS vdaka volaniu ABSTRACT METHOD INTERFACE CLASS deleguje pracu s CALLBACK TYPE na DERIVED CLASSES z INTERFACE CLASS.
				bool											Result=Function1.MBridge->Equals(Function2.MBridge);

				return(Result);
			}
		}

		friend bool operator!=(const CTypeErasureCallbackWrapper& Function1, const CTypeErasureCallbackWrapper& Function2)
		{
			bool												Result=!(Function1==Function2);

			return(Result);
		}

	private:
		friend void Swap(CTypeErasureCallbackWrapper& Object1, CTypeErasureCallbackWrapper& Object2)
		{
			// !!!!! FUNCTION [swap()] je implementovana pre POINTERS na FUNCTION, REFERENCES na FUNCTION. Genericka verzia obsahuje SWAP aj pre bezne REFERENCE TYPES, takze ju je mozne pouzit aj na SWAP CUSTOM FUNCTION OBJECTS ci LAMBDA FUNCTIONS.
			std::swap(Object1.MBridge,Object2.MBridge);
		}

	private:
		// !!!!! TEMPLATE CLASS skryva pouzitie CALLBACK TYPE za INTERFACE CLASS, na ktory sa referuje pomocou POINTER.
		// !!!!! Kedze INTERFACE CLASS NEOBSAHUJE ani TEMPLATE PARAMETER samotny CALLBACK TYPE, tak NIE JE INSTANTIATED pre KAZDY CALLBACK TYPE.
		CTypeErasureCallbackWrapperBridgeInterface<TReturnValue,TParameters...>*	MBridge;

	public:
		CTypeErasureCallbackWrapper& operator=(const CTypeErasureCallbackWrapper& Other);
		CTypeErasureCallbackWrapper& operator=(CTypeErasureCallbackWrapper&& Other);

	public:
		template<typename TFunction>
		CTypeErasureCallbackWrapper& operator=(TFunction&& Function);

	public:
		TReturnValue operator()(TParameters... Parameters) const;

	public:
		explicit operator bool(void) const;

	public:
		CTypeErasureCallbackWrapper(void);
		CTypeErasureCallbackWrapper(const CTypeErasureCallbackWrapper& Other);
		CTypeErasureCallbackWrapper(CTypeErasureCallbackWrapper& Other);
		CTypeErasureCallbackWrapper(CTypeErasureCallbackWrapper&& Other);

	public:
		// !!!!! CONSTRUCTOR umoznujuci nastavit CALLBACK FUNCTION.
		template<typename TFunction>
		CTypeErasureCallbackWrapper(TFunction&& Function);

	public:
		virtual ~CTypeErasureCallbackWrapper(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::CTypeErasureCallbackWrapper(void)
	: MBridge(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::CTypeErasureCallbackWrapper(const CTypeErasureCallbackWrapper& Other)
	: MBridge(nullptr)
{
	if (Other.MBridge!=nullptr)
	{
		// !!!!! Vola sa VIRTUAL METHOD INTERFACE CLASS, ktora vytvori CLONE daneho OBJECT.
		// !!!!! TEMPLATE CLASS vdaka volaniu ABSTRACT METHOD INTERFACE CLASS deleguje pracu s CALLBACK TYPE na DERIVED CLASSES z INTERFACE CLASS.
		MBridge=Other.MBridge->Clone();
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::CTypeErasureCallbackWrapper(CTypeErasureCallbackWrapper& Other)
	: CTypeErasureCallbackWrapper(static_cast<const CTypeErasureCallbackWrapper&>(Other))
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::CTypeErasureCallbackWrapper(CTypeErasureCallbackWrapper&& Other)
	: MBridge(Other.Mridge)
{
	Other.MBridge=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tento TEMPLATE CONSTRUCTOR je na rozdiel od ostatnych METHODS tejto TEMPLATE CLASS je INSTANTIATED pre KAZDY CALLBACK TYPE, kedze ako TEMPLATE PARAMETER obsahuje CALLBACK TYPE. Jedna sa vsak iba o jednu METHOD a nie celu TEMPLATE CLASS.
template<typename TReturnValue, typename... TParameters>
template<typename TFunction>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::CTypeErasureCallbackWrapper(TFunction&& Function)
	: MBridge(nullptr)
{
	// !!!!! CODE [decay_t<TFunction>] odstranenim MODIFIER [const] a MODIFIER [volatile] vracia TYPE, ktoreho instancie mozu byt STORED.
	using														FunctionObject=std::decay_t<TFunction>;

	// !!!!! TYPE reprezentuje DERIVED CLASS pre konkretny CALLBACK TYPE reprezentovany TEMPLATE PARAMETER [TFunction], ktorej instancie sa bude vytvarat.
	using														Bridge=CTypeErasureCallbackWrapperBridgeImplementation<FunctionObject,TReturnValue,TParameters...>;

	// !!!!! CODE vytvori instanciu DERIVED CLASS pre konkretny CALLBACK TYPE reprezentovany TEMPLATE PARAMETER [TFunction].
	MBridge=new Bridge(std::forward<TFunction>(Function));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::~CTypeErasureCallbackWrapper(void) noexcept
{
	delete(MBridge);

	MBridge=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>& CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::operator=(const CTypeErasureCallbackWrapper& Other)
{
	CTypeErasureCallbackWrapper											Object(Other);

	Swap(*this,Object);

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>& CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::operator=(CTypeErasureCallbackWrapper&& Other)
{
	delete(MBridge);

	MBridge=Other.MBridge;

	Other.MBridge=nullptr;

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Tento OPERATOR [OPERATOR=] je na rozdiel od ostatnych METHODS tejto TEMPLATE CLASS je INSTANTIATED pre KAZDY CALLBACK TYPE, kedze ako TEMPLATE PARAMETER obsahuje CALLBACK TYPE. Jedna sa vsak iba o jednu METHOD a nie celu TEMPLATE CLASS.
template<typename TReturnValue, typename... TParameters>
template<typename TFunction>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>& CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::operator=(TFunction&& Function)
{
	// !!!!! Vola sa TEMPLATE CONSTRUCTOR.
	CTypeErasureCallbackWrapper									Object(std::forward<TFunction>(Function));

	Swap(*this,Object);

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
TReturnValue CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::operator()(TParameters... Parameters) const
{
	// !!!!! Vola sa VIRTUAL METHOD INTERFACE CLASS, ktora ktora spusti CODE CALLBACK TYPE.
	// !!!!! TEMPLATE CLASS vdaka volaniu ABSTRACT METHOD INTERFACE CLASS deleguje pracu s CALLBACK TYPE na DERIVED CLASSES z INTERFACE CLASS.
	return(MBridge->Invoke(std::forward<TParameters>(Parameters)...));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename... TParameters>
CTypeErasureCallbackWrapper<TReturnValue(TParameters...)>::operator bool(void) const
{
	bool														IsNull=(MBridge==nullptr);

	return(IsNull);
}
//----------------------------------------------------------------------------------------------------------------------