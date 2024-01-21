//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <type_traits>
#include "STypeTraitEnableIfType.h"
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PRIMARY TEMPLATE CLASS, ktora sluzi ako DEFAULT CASE.
template<typename TType, typename HIDDEN=void>
struct SClassTemplateEnableDisable final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		void Print(void) const;

	public:
		SClassTemplateEnableDisable(TType Value);
		virtual ~SClassTemplateEnableDisable(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename HIDDEN>
SClassTemplateEnableDisable<TType,HIDDEN>::SClassTemplateEnableDisable(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename HIDDEN>
SClassTemplateEnableDisable<TType,HIDDEN>::~SClassTemplateEnableDisable(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename HIDDEN>
void SClassTemplateEnableDisable<TType,HIDDEN>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE CLASS - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_integral<TType>::value==true>> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		void Print(void) const;

	public:
		SClassTemplateEnableDisable(TType Value);
		virtual ~SClassTemplateEnableDisable(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_integral<TType>::value==true>> ::SClassTemplateEnableDisable(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_integral<TType>::value==true>>::~SClassTemplateEnableDisable(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_integral<TType>::value==true>>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS SPECALIZATION for INTEGER TYPES - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_floating_point<TType>::value==true>> final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		void Print(void) const;

	public:
		SClassTemplateEnableDisable(TType Value);
		virtual ~SClassTemplateEnableDisable(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_floating_point<TType>::value==true>> ::SClassTemplateEnableDisable(TType Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_floating_point<TType>::value==true>>::~SClassTemplateEnableDisable(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void SClassTemplateEnableDisable<TType,STypeTraitEnableIfAlias<std::is_floating_point<TType>::value==true>>::Print(void) const
{
	std::wcout << L"TEMPLATE CLASS SPECALIZATION for FLOATING POINT TYPES - TYPE [" << GetTypeInfoName<decltype(MValue)>() << L"] VALUE [" << MValue << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------