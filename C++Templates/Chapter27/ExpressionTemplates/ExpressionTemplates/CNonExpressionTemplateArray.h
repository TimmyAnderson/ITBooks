//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CException.h"
#include "CDouble.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CNonExpressionTemplateArray
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType*													MStorage;
		size_t													MStorageSize;

	public:
		CNonExpressionTemplateArray<TType>& operator=(const CNonExpressionTemplateArray<TType>& Array);

	public:
		const TType& operator[](size_t Index) const;
		TType& operator[](size_t Index);

	public:
		CNonExpressionTemplateArray<TType>& operator+=(const CNonExpressionTemplateArray<TType>& Array);
		CNonExpressionTemplateArray<TType>& operator*=(const CNonExpressionTemplateArray<TType>& Array);
		CNonExpressionTemplateArray<TType>& operator*=(const TType& Value);

	protected:
		void Init(void);
		void Copy(const CNonExpressionTemplateArray<TType>& Array);

	public:
		size_t Size(void) const;

	public:
		explicit CNonExpressionTemplateArray(size_t Size);
		CNonExpressionTemplateArray(const CNonExpressionTemplateArray<TType>& Value);
		virtual ~CNonExpressionTemplateArray(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CNonExpressionTemplateArray<TType>::CNonExpressionTemplateArray(size_t Size)
	: MStorage(new TType[Size]), MStorageSize(Size)
{
	Init();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CNonExpressionTemplateArray<TType>::CNonExpressionTemplateArray(const CNonExpressionTemplateArray<TType>& Value)
	: MStorage(new TType[Value.Size()]), MStorageSize(Value.Size())
{
	Copy(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CNonExpressionTemplateArray<TType>::~CNonExpressionTemplateArray(void) noexcept
{
	delete[](MStorage);
	MStorage=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CNonExpressionTemplateArray<TType>& CNonExpressionTemplateArray<TType>::operator=(const CNonExpressionTemplateArray<TType>& Array)
{
	if (&Array!=this)
	{
		Copy(Array);
	}
	
	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const TType& CNonExpressionTemplateArray<TType>::operator[](size_t Index) const
{
	const TType&												Result=MStorage[Index];

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
TType& CNonExpressionTemplateArray<TType>::operator[](size_t Index)
{
	TType&														Result=MStorage[Index];

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType>& CNonExpressionTemplateArray<TType>::operator+=(const CNonExpressionTemplateArray<TType>& Array)
{
	if (Size()!=Array.Size())
	{
		throw(CException(L"ARRAYS must have the SAME SIZES."));
	}

	for (size_t Index=0;Index<Size();++Index)
	{
		(*this)[Index]+=Array[Index];
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType>& CNonExpressionTemplateArray<TType>::operator*=(const CNonExpressionTemplateArray<TType>& Array)
{
	if (Size()!=Array.Size())
	{
		throw(CException(L"ARRAYS must have the SAME SIZES."));
	}

	for (size_t Index=0;Index<Size();++Index)
	{
		(*this)[Index]*=Array[Index];
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! MEMBER OPERATOR NEVYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType>& CNonExpressionTemplateArray<TType>::operator*=(const TType& Value)
{
	for (size_t Index=0;Index<Size();++Index)
	{
		(*this)[Index]*=Value;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CNonExpressionTemplateArray<TType>::Init(void)
{
	for (size_t Index=0;Index<Size();++Index)
	{
		MStorage[Index]=TType();
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CNonExpressionTemplateArray<TType>::Copy(const CNonExpressionTemplateArray<TType>& Array)
{
	if (Size()!=Array.Size())
	{
		throw(CException(L"ARRAYS must have the SAME SIZE."));
	}

	for (size_t Index=0;Index<Size();++Index)
	{
		MStorage[Index]=Array.MStorage[Index];
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
size_t CNonExpressionTemplateArray<TType>::Size(void) const
{
	return(MStorageSize);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType> operator+(const CNonExpressionTemplateArray<TType>& Array1, const CNonExpressionTemplateArray<TType>& Array2)
{
	if (Array1.Size()!=Array2.Size())
	{
		throw(CException(L"ARRAYS must have the SAME SIZE."));
	}

	CNonExpressionTemplateArray<TType>							Result(Array1.Size());

	for (size_t Index=0;Index<Array1.Size();++Index)
	{
		Result[Index]=(Array1[Index]+Array2[Index]);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType> operator*(const CNonExpressionTemplateArray<TType>& Array1, const CNonExpressionTemplateArray<TType>& Array2)
{
	if (Array1.Size()!=Array2.Size())
	{
		throw(CException(L"ARRAYS must have the SAME SIZES."));
	}

	CNonExpressionTemplateArray<TType>							Result(Array1.Size());

	for (size_t Index=0;Index<Array1.Size();++Index)
	{
		Result[Index]=(Array1[Index]*Array2[Index]);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! NON-MEMBER OPERATOR VYTVARA TEMPORARY ARRAY.
template<typename TType>
CNonExpressionTemplateArray<TType> operator*(const TType& Value, const CNonExpressionTemplateArray<TType>& Array)
{
	CNonExpressionTemplateArray<TType>							Result(Array.Size());

	for (size_t Index=0;Index<Array.Size();++Index)
	{
		Result[Index]=(Value*Array[Index]);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------