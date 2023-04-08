//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
template<typename TFriendType>
class CFriendlyTemplate;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CComplexTemplate
{
//-------------------------------------------------------------------------------------------------------
	private:
		TType													MPrivateMember;

	public:
		int														MVariable1=100;
		TType													MVariable2;
		static int												MStaticVariable1;
		static TType											MStaticVariable2;
		static const int										MStaticConstVariable1=300;
		static const TType										MStaticConstVariable2;

	public:
		// Deklaracia TEMPLATE CLASS ako FRIEND. Podobne sa daju deklarovat aj FUNCTION ci OPERATORS.
		template<typename TFriendType>
		friend class CFriendlyTemplate;

	public:
		void SetPrivateMember(TType Value)
		{
			MPrivateMember=Value;
		}

		TType GetVariable2(void)
		{
			return(MVariable2);
		}

		static TType GetStaticVariable2(void)
		{
			return(MStaticVariable2);
		}

	public:
		// !!! Priklad TEMPLATE METHOD.
		template<typename TMethodType>
		TMethodType Convert(void) const
		{
			TType													Value=MVariable2;
			TMethodType												ConvertedValue=(TMethodType) Value;

			return(ConvertedValue);
		}

	public:
		// !!! Priklad TEMPLATE OPERATOR.
		template<typename TMethodType>
		operator TMethodType(void) const
		{
			TType													Value=MVariable2;
			TMethodType												ConvertedValue=(TMethodType) Value;

			return(ConvertedValue);
		}

	public:
		// !!! USING a TYPEDEF definuju TYPE ALIASES.
		using CUnderlyingType=TType;
		typedef TType* CUnderlyingTypePointer;

	public:
		struct SInnerStruct1
		{
//-------------------------------------------------------------------------------------------------------
			public:
				TType											MValue;
//-------------------------------------------------------------------------------------------------------
		};

		// !!! Dopredna deklaracia.
		struct SInnerStruct2;

	public:
		template<typename TNestedType>
		class CNestedTemplate
		{
//-------------------------------------------------------------------------------------------------------
			public:
				TNestedType										MNestedValue;
//-------------------------------------------------------------------------------------------------------
		};

		enum EInnerEnum1
		{
//-------------------------------------------------------------------------------------------------------
			E_YES=1,
			E_NO=0
//-------------------------------------------------------------------------------------------------------
		};

		// !!! Dopredna deklaracia.
		//enum EInnerEnum2 : int;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
int CComplexTemplate<TType>::MStaticVariable1=200;
//-------------------------------------------------------------------------------------------------------
template<typename TType>
TType CComplexTemplate<TType>::MStaticVariable2;
//-------------------------------------------------------------------------------------------------------
template<typename TType>
const TType CComplexTemplate<TType>::MStaticConstVariable2=TType();
//-------------------------------------------------------------------------------------------------------
// !!! Specializacia pre [wstring].
template<>
const wstring CComplexTemplate<wstring>::MStaticConstVariable2=L"Jenny";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
struct CComplexTemplate<TType>::SInnerStruct2
{
//-------------------------------------------------------------------------------------------------------
	public:
		TType													MValueOutside;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/*
template<typename TType>
enum CComplexTemplate<TType>::EInnerEnum2 : int
{
//-------------------------------------------------------------------------------------------------------
	E_X=1,
	E_Y=2
//-------------------------------------------------------------------------------------------------------
};
*/
//-------------------------------------------------------------------------------------------------------