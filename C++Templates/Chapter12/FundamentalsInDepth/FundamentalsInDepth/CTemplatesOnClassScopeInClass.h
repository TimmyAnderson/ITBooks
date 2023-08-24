//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS na NAMESPACE SCOPE.
template<typename TType>
class CTemplatesOnClassScopeInClassOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! TEMPLATE CLASS na CLASS SCOPE.
		template<typename TInnerType>
		class CTemplatesOnClassScopeInClassInner final
		{
//----------------------------------------------------------------------------------------------------------------------
			private:
				TInnerType											MField;

			public:
				// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
				const TInnerType& GetField(void) const noexcept
				{
					return(MField);
				}

			public:
				// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE.
				CTemplatesOnClassScopeInClassInner(TInnerType Value)
					: MField(Value)
				{
				}

				// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE.
				virtual ~CTemplatesOnClassScopeInClassInner(void) noexcept
				{
				}
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! TEMPLATE TYPE ALIAS na CLASS SCOPE.
		template<typename TInnerType>
		using													TemplateTypeAliasOnClassScopeInClass=CTemplatesOnClassScopeInClassInner<TInnerType*>;

	public:
		// !!! TEMPLATE STATIC FIELD na CLASS SCOPE.
		// !!!!! TEMPLATE STATIC FIELD MUSI byt oznaceny pomocou KEYWORD [inline].
		template<typename TInnerType>
		inline static TInnerType								MTemplateStaticFieldOnClassScopeInClass{};

	private:
		TType													MField1;
		CTemplatesOnClassScopeInClassInner<TType>				MField2;

	public:
		// !!! TEMPLATE METHOD na CLASS SCOPE.
		template<typename TInnerType>
		void TemplateMetodOnClassScopeInClass(TType Value1, TInnerType Value2) const
		{
			std::wcout << L"TEMPLATE METHOD ON CLASS SCOPE - VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
		}

	public:
		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const TType& GetField1(void) const noexcept
		{
			return(MField1);
		}

		// !!! NON-TEMPLATE METHOD na CLASS SCOPE.
		const CTemplatesOnClassScopeInClassInner<TType>& GetField2(void) const noexcept
		{
			return(MField2);
		}

	public:
		// !!! NON-TEMPLATE CONSTRUCTOR na CLASS SCOPE.
		CTemplatesOnClassScopeInClassOuter(TType Value1, CTemplatesOnClassScopeInClassInner<TType> Value2)
			: MField1(Value1), MField2(Value2)
		{
		}

		// !!! NON-TEMPLATE DESTRUCTOR na CLASS SCOPE.
		virtual ~CTemplatesOnClassScopeInClassOuter(void) noexcept
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------