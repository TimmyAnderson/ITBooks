//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <cassert>
#include <utility>
#include "CException.h"
#include "CComputedResultType.h"
#include "CTypeList.h"
#include "CTypeListFront.h"
#include "CVariantStorage.h"
#include "CVariantChoice.h"
#include "CVisitResultType.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 26439 )
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! CLASS dedi z 1 INSTANCIE CLASS [CVariantStorage<TTypes...>] a N INSTANCII CLASS [CVariantChoice<TTypes,TTypes...>], kde VALUE 'N' je pocet TYPES, ktore mozu byt ulozene vo VARIANT.
template<typename... TTypes>
class CVariant : private CVariantStorage<TTypes...>, private CVariantChoice<TTypes,TTypes...>...
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TOtherType, typename... TOtherTypes>
	friend class CVariantChoice;

	public:
		// !!!!! CODE vlozi do CLASS [CVariant] vsetky OPERATOR [OPERATOR=] z DERIVED CLASSES [CVariantChoice<TTypes,TTypes...>].
		using CVariantChoice<TTypes,TTypes...>::operator=...;

	public:
		// !!!!! CODE vlozi do CLASS [CVariant] vsetky CONSTRUCTORS z DERIVED CLASSES [CVariantChoice<TTypes,TTypes...>].
		using CVariantChoice<TTypes,TTypes...>::CVariantChoice...;

	public:
		CVariant& operator=(const CVariant& Source);
		CVariant& operator=(CVariant&& Source);
		template<typename... TSourceTypes>
		CVariant& operator=(const CVariant<TSourceTypes...>& Source);
		template<typename... TSourceTypes>
		CVariant& operator=(CVariant<TSourceTypes...>&& Source);

	public:
		bool Empty(void) const;
		void Destroy(void);

	public:
		template<typename TType>
		bool Is(void) const;
		template<typename TType>
		TType& Get(void)&;
		template<typename TType>
		const TType& Get(void) const&;

	public:
		template<typename TReturnValue=CComputedResultType, typename TVisitor>
		CVisitResult<TReturnValue,TVisitor,TTypes&...> Visit(TVisitor&& Visitor) &;
		template<typename TReturnValue=CComputedResultType, typename TVisitor>
		CVisitResult<TReturnValue,TVisitor,const TTypes&...> Visit(TVisitor&& Visitor) const&;
		template<typename TReturnValue=CComputedResultType, typename TVisitor>
		CVisitResult<TReturnValue,TVisitor,TTypes&&...> Visit(TVisitor&& Visitor) &&;

	public:
		CVariant(void);
		CVariant(const CVariant& Source);
		CVariant(CVariant&& Source);
		template<typename... TSourceTypes>
		CVariant(const CVariant<TSourceTypes...>& Source);
		template<typename... TSourceTypes>
		CVariant(CVariant<TSourceTypes...>&& Source);
		virtual ~CVariant(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue, typename TType, typename TVisitor, typename THead, typename... TTail>
TReturnValue VariantVisit(TType&& Variant, TVisitor&& Visitor, CTypeList<THead,TTail...>);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>::CVariant(void)
{
	*this=CTypeListFront<CTypeList<TTypes...>>();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>::CVariant(const CVariant& Source)
	: CVariantStorage<TTypes...>(), CVariantChoice<TTypes,TTypes...>()...
{
	if (Source.Empty()==false)
	{
		Source.Visit([&](const auto& Value) {*this=Value;});
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>::CVariant(CVariant&& Source)
	: CVariantStorage<TTypes...>(), CVariantChoice<TTypes,TTypes...>()...
{
	if (Source.Empty()==false)
	{
		std::move(Source).Visit([&](auto&& Value) {*this=std::move(Value);});
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename... TSourceTypes>
CVariant<TTypes...>::CVariant(const CVariant<TSourceTypes...>& Source)
	: CVariantStorage<TTypes...>(), CVariantChoice<TTypes,TTypes...>()...
{
	if (Source.Empty()==false)
	{
		Source.Visit([&](const auto& Value) {*this=Value;});
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename... TSourceTypes>
CVariant<TTypes...>::CVariant(CVariant<TSourceTypes...>&& Source)
	: CVariantStorage<TTypes...>(), CVariantChoice<TTypes,TTypes...>()...
{
	if (Source.Empty()==false)
	{
		std::move(Source).Visit([&](auto&& Value) {*this=std::move(Value);});
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>::~CVariant(void) noexcept
{
	Destroy();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>& CVariant<TTypes...>::operator=(const CVariant& Source)
{
	if (Source.Empty()==false)
	{
		Source.Visit([&](const auto& Value){*this=Value;});
	}
	else
	{
		Destroy();
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
CVariant<TTypes...>& CVariant<TTypes...>::operator=(CVariant&& Source)
{
	if (Source.Empty()==false)
	{
		std::move(Source).Visit([&](auto&& Value){*this=std::move(Value);});
	}
	else
	{
		Destroy();
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename... TSourceTypes>
CVariant<TTypes...>& CVariant<TTypes...>::operator=(const CVariant<TSourceTypes...>& Source)
{
	if (Source.Empty()==false)
	{
		Source.Visit([&](auto const& Value){*this=Value;});
	}
	else
	{
		Destroy();
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename... TSourceTypes>
CVariant<TTypes...>& CVariant<TTypes...>::operator=(CVariant<TSourceTypes...>&& Source)
{
	if (Source.Empty()==false)
	{
		std::move(Source).Visit([&](auto&& Value){*this=std::move(Value);});
	}
	else
	{
		Destroy();
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
bool CVariant<TTypes...>::Empty(void) const
{
	uint8_t														Discriminator=this->GetDiscriminator();
	bool														Result=(Discriminator==0);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
void CVariant<TTypes...>::Destroy(void)
{
	// !!!!! Vola sa METHOD [bool CVariantChoice::Destroy(void)] pre vsetky BASE CLASS [CVariantChoice]. MEMORY uvolni iba ta METHOD [bool CVariantChoice::Destroy(void)], ktore instancia CLASS [CVariantChoice] obsahuje VALUE.
	(CVariantChoice<TTypes,TTypes...>::Destroy(),...);

	// !!! DISCRIMINATOR sa nastavi na 0 co znamena, ze neobsahuje ziadnu VALUE.
	this->SetDiscriminator(0);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TType>
bool CVariant<TTypes...>::Is(void) const
{ 
	bool														Result=(this->GetDiscriminator()==CVariantChoice<TType,TTypes...>::Discriminator);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TType>
TType& CVariant<TTypes...>::Get(void) &
{
	if (Empty()==true)
	{
		throw(CException(L"VARIANT is EMPTY !"));
	}

	if (Is<TType>()==false)
	{
		throw(CException(L"VARIANT has a DIFFERENT TYPE !"));
	}

	TType&														Result=*this->template GetBufferAs<TType>();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TType>
const TType& CVariant<TTypes...>::Get(void) const &
{
	if (Empty()==true)
	{
		throw(CException(L"VARIANT is EMPTY !"));
	}

	if (Is<TType>()==false)
	{
		throw(CException(L"VARIANT has a DIFFERENT TYPE !"));
	}

	const TType&												Result=*this->template GetBufferAs<TType>();

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TReturnValue, typename TVisitor>
CVisitResult<TReturnValue,TVisitor,TTypes&...> CVariant<TTypes...>::Visit(TVisitor&& Visitor)&
{
	using														ResultType=CVisitResult<TReturnValue,TVisitor,TTypes&...>;

	return(VariantVisit<ResultType>(*this,std::forward<TVisitor>(Visitor),CTypeList<TTypes...>()));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TReturnValue, typename TVisitor>
CVisitResult<TReturnValue,TVisitor,const TTypes&...> CVariant<TTypes...>::Visit(TVisitor&& Visitor) const&
{
	using														ResultType=CVisitResult<TReturnValue,TVisitor,const TTypes&...>;

	return VariantVisit<ResultType>(*this,std::forward<TVisitor>(Visitor),CTypeList<TTypes...>());
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TTypes>
template<typename TReturnValue, typename TVisitor>
CVisitResult<TReturnValue,TVisitor,TTypes&&...> CVariant<TTypes...>::Visit(TVisitor&& Visitor) &&
{
	using														ResultType=CVisitResult<TReturnValue,TVisitor,TTypes&&...>;

	return(VariantVisit<ResultType>(std::move(*this),std::forward<TVisitor>(Visitor),CTypeList<TTypes...>()));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FUNCTION impelmentuje VISITOR PATTERN.
template<typename TReturnValue, typename TType, typename TVisitor, typename THead, typename... TTail>
TReturnValue VariantVisit(TType&& Variant, TVisitor&& Visitor, CTypeList<THead,TTail...>)
{
	if (Variant.template Is<THead>()==true)
	{
		return(static_cast<TReturnValue>(std::forward<TVisitor>(Visitor)(std::forward<TType>(Variant).template Get<THead>())));
	}
	else if constexpr (sizeof...(TTail)>0)
	{
		return(VariantVisit<TReturnValue>(std::forward<TType>(Variant),std::forward<TVisitor>(Visitor),CTypeList<TTail...>()));
	}
	else
	{
		throw(CException(L"VARIANT is EMPTY."));
	}
}
//----------------------------------------------------------------------------------------------------------------------