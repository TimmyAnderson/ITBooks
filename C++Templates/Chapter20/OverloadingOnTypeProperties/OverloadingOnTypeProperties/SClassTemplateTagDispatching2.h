//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CClassTagDisptaching1.h"
#include "CClassTagDisptaching2.h"
#include "CClassTagDisptaching3.h"
#include "STypeTraitBestTypeMatchType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION PRIMARY TEMPLATE CLASS.
// !!!!! 2. TEMPLATE PARAMETER sa pouziva na rozlisenie, ktoru TEMPLATE CLASS SPECIALIZATION ma COMPILER pouzit.
// !!!!! 2. TEMPLATE PARAMETER ma nastaveny DEFAULT ARGUMENT co je TYPE TRAIT urcujuci, ktora TEMPLATE CLASS SPECIALIZATION sa ma pouzit. Vyuziva sa fakt, ze DEFAULT ARGUMENT pre TEMPLATE PARAMETERS su AUTOMATICKY prenasane do TEMPLATE CLASS SPECIALIZATIONS.
template<typename TType, typename TTag=STypeTraitBestTypeMatchAlias<typename TType::TAG,CClassTagDisptaching1,CClassTagDisptaching2,CClassTagDisptaching3>>
struct SClassTemplateTagDispatching2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION pre TAG DISPATCHING CLASS [CClassTagDisptaching1].
template<typename TType>
struct SClassTemplateTagDispatching2<TType,CClassTagDisptaching1>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(TType Value) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SClassTemplateTagDispatching2<TType,CClassTagDisptaching1>::Print(TType Value) const
{
	std::wcout << L"2 - TEMPLATE CLASS SPECALIZATION for TAG DISPATCHING 1 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION pre TAG DISPATCHING CLASS [CClassTagDisptaching2].
template<typename TType>
struct SClassTemplateTagDispatching2<TType,CClassTagDisptaching2>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(TType Value) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SClassTemplateTagDispatching2<TType,CClassTagDisptaching2>::Print(TType Value) const
{
	std::wcout << L"2 - TEMPLATE CLASS SPECALIZATION for TAG DISPATCHING 2 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS SPECIALIZATION pre TAG DISPATCHING CLASS [CClassTagDisptaching3].
template<typename TType>
struct SClassTemplateTagDispatching2<TType,CClassTagDisptaching3>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(TType Value) const;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SClassTemplateTagDispatching2<TType,CClassTagDisptaching3>::Print(TType Value) const
{
	std::wcout << L"2 - TEMPLATE CLASS SPECALIZATION for TAG DISPATCHING 3 - TYPE [" << GetTypeInfoName<decltype(Value)>() << L"] VALUE [" << Value << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------