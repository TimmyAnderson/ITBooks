//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CNonExpressionTemplateArray.h"
#include "CException.h"
#include "CExpressionTemplateAdd.h"
#include "CExpressionTemplateMultiple.h"
#include "CExpressionTemplateScalar.h"
#include "CExpressionTemplateSubscript.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! 1. TEMPLATE PARAMETER urcuje TYPE EXPRESSION a 2. TEMPLATE PARAMETER je bud realny ARRAY, alebo ina instancia CLASS [CExpressionTemplateAdd], alebo CLASS [CExpressionTemplateMultiple].
template<typename TType, typename TRepresentation=CNonExpressionTemplateArray<TType>>
class CExpressionTemplateArray final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TRepresentation											MExpressionRepresentation;

	public:
		CExpressionTemplateArray& operator=(const CExpressionTemplateArray& Other);
		template<typename TTypeOther, typename TRepresentationOther>
		CExpressionTemplateArray& operator=(const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other);

	public:
		template<typename TTypeOther, typename TRepresentationOther>
		CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>> operator[](const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other);
		template<typename TTypeOther, typename TRepresentationOther>
		CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>> operator[](const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other) const;

	public:
		decltype(auto) operator[](size_t Index) const;
		TType& operator[](size_t Index);

	public:
		size_t Size(void) const;
		const TRepresentation& Representation(void) const;
		TRepresentation& Representation(void);

	public:
		explicit CExpressionTemplateArray(size_t Size);
		CExpressionTemplateArray(const TRepresentation& Other);
		virtual ~CExpressionTemplateArray(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,TRepresentation>::CExpressionTemplateArray(size_t Size)
	: MExpressionRepresentation(Size)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,TRepresentation>::CExpressionTemplateArray(const TRepresentation& Other)
	: MExpressionRepresentation(Other)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,TRepresentation>::~CExpressionTemplateArray(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
decltype(auto) CExpressionTemplateArray<TType,TRepresentation>::operator[](size_t Index) const
{
	if (Index>=Size())
	{
		throw(CException(L"INDEX if OUT of BOUNDS."));
	}

	return(MExpressionRepresentation[Index]);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
TType& CExpressionTemplateArray<TType,TRepresentation>::operator[](size_t Index)
{
	if (Index>=Size())
	{
		throw(CException(L"INDEX if OUT of BOUNDS."));
	}

	return(MExpressionRepresentation[Index]);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,TRepresentation>& CExpressionTemplateArray<TType,TRepresentation>::operator=(const CExpressionTemplateArray& Other)
{
	if (Size()!=Other.Size())
	{
		throw(CException(L"SIZES are NOT EQUAL."));
	}

	for (size_t Index=0; Index<Other.Size();++Index)
	{
		MExpressionRepresentation[Index]=Other[Index];
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
template<typename TTypeOther, typename TRepresentationOther>
CExpressionTemplateArray<TType,TRepresentation>& CExpressionTemplateArray<TType,TRepresentation>::operator=(const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other)
{
	if (Size()!=Other.Size())
	{
		throw(CException(L"SIZES are NOT EQUAL."));
	}

	for (size_t Index=0;Index<Other.Size();++Index)
	{
		MExpressionRepresentation[Index]=Other[Index];
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
template<typename TTypeOther, typename TRepresentationOther>
CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>> CExpressionTemplateArray<TType,TRepresentation>::operator[](const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>>;

	return(TYPE(CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>(this->Representation(),Other.Representation())));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
template<typename TTypeOther, typename TRepresentationOther>
CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>> CExpressionTemplateArray<TType,TRepresentation>::operator[](const CExpressionTemplateArray<TTypeOther,TRepresentationOther>& Other) const
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>>;

	return(TYPE(CExpressionTemplateSubscript<TType,TRepresentation,TRepresentationOther>(*this,Other)));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
size_t CExpressionTemplateArray<TType,TRepresentation>::Size(void) const
{
	size_t														Size=MExpressionRepresentation.Size();

	return(Size);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
const TRepresentation& CExpressionTemplateArray<TType,TRepresentation>::Representation(void) const
{
	return(MExpressionRepresentation);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TRepresentation>
TRepresentation& CExpressionTemplateArray<TType,TRepresentation>::Representation(void)
{
	return(MExpressionRepresentation);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [ARRAY_1+ARRAY_2].
template<typename TType, typename TRepresentation1, typename TRepresentation2>
CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,TRepresentation1,TRepresentation2>> operator+(const CExpressionTemplateArray<TType,TRepresentation1>& Array1, const CExpressionTemplateArray<TType,TRepresentation2>& Array2)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,TRepresentation1,TRepresentation2>>;

    return(TYPE(CExpressionTemplateAdd<TType,TRepresentation1,TRepresentation2>(Array1.Representation(),Array2.Representation())));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [SCALAR+ARRAY].
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,CExpressionTemplateScalar<TType>,TRepresentation>> operator+(const TType& Scalar, const CExpressionTemplateArray<TType,TRepresentation>& Array)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,CExpressionTemplateScalar<TType>,TRepresentation>>;

    return(TYPE(CExpressionTemplateAdd<TType,CExpressionTemplateScalar<TType>,TRepresentation>(CExpressionTemplateScalar<TType>(Scalar),Array.Representation())));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [ARRAY+SCALAR].
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,TRepresentation,CExpressionTemplateScalar<TType>>> operator+(const CExpressionTemplateArray<TType,TRepresentation>& Array, const TType& Scalar)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateAdd<TType,TRepresentation,CExpressionTemplateScalar<TType>>>;

    return(TYPE(CExpressionTemplateAdd<TType,TRepresentation,CExpressionTemplateScalar<TType>>(Array.Representation(),CExpressionTemplateScalar<TType>(Scalar))));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [ARRAY_1*ARRAY_2].
template<typename TType, typename TRepresentation1, typename TRepresentation2>
CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,TRepresentation1,TRepresentation2>> operator*(const CExpressionTemplateArray<TType,TRepresentation1>& Array1, const CExpressionTemplateArray<TType,TRepresentation2>& Array2)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,TRepresentation1,TRepresentation2>>;

    return(TYPE(CExpressionTemplateMultiple<TType,TRepresentation1,TRepresentation2>(Array1.Representation(),Array2.Representation())));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [SCALAR*ARRAY].
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,CExpressionTemplateScalar<TType>,TRepresentation>> operator*(const TType& Scalar, const CExpressionTemplateArray<TType,TRepresentation>& Array)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,CExpressionTemplateScalar<TType>,TRepresentation>>;

	return(TYPE(CExpressionTemplateMultiple<TType,CExpressionTemplateScalar<TType>,TRepresentation>(CExpressionTemplateScalar<TType>(Scalar),Array.Representation())));
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! OPERATOR NESPUSTA EXPRESSION EVALUATION.
// !!!!! Vytvara ARRAY pre OPERATION [ARRAY*SCALAR].
template<typename TType, typename TRepresentation>
CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,TRepresentation,CExpressionTemplateScalar<TType>>> operator*(const CExpressionTemplateArray<TType,TRepresentation>& Array, const TType& Scalar)
{
	using														TYPE=CExpressionTemplateArray<TType,CExpressionTemplateMultiple<TType,TRepresentation,CExpressionTemplateScalar<TType>>>;

    return(TYPE(CExpressionTemplateMultiple<TType,TRepresentation,CExpressionTemplateScalar<TType>>(Array.Representation(),CExpressionTemplateScalar<TType>(Scalar))));
}
//----------------------------------------------------------------------------------------------------------------------