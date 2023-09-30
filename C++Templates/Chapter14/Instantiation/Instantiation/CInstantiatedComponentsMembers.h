//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CInstantiatedComponentsMembersSafe final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Ak je VALUE SIZE<=0, tak COMPILER hodi ERROR.
template<int SIZE>
class CInstantiatedComponentsMembersDanger
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MArray[SIZE];

	public:
		int GetArrayItem(int Index);
		void SetArrayItem(int Index, int Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<int SIZE>
int CInstantiatedComponentsMembersDanger<SIZE>::GetArrayItem(int Index)
{
	if (Index<0 || Index>=SIZE)
	{
		throw(CException(L"ARRAY is OUT of BOUNDS."));
	}

	int															Value=MArray[Index];

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<int SIZE>
void CInstantiatedComponentsMembersDanger<SIZE>::SetArrayItem(int Index, int Value)
{
	if (Index<0 || Index>=SIZE)
	{
		throw(CException(L"ARRAY is OUT of BOUNDS."));
	}

	MArray[Index]=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int SIZE>
class CInstantiatedComponentsMembers final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		class CInstantiatedComponentsMembersNested final
		{
//----------------------------------------------------------------------------------------------------------------------
			private:
				// !!! Ak je VALUE SIZE<=0, tak COMPILER hodi ERROR.
				CInstantiatedComponentsMembersDanger<SIZE>		MArray;

			public:
				int GetArrayItem(int Index);
				void SetArrayItem(int Index, int Value);
//----------------------------------------------------------------------------------------------------------------------
		};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! ANONYMOUS UNION.
		union
		{
			public:
				// !!! Ak je VALUE SIZE<=0, tak COMPILER hodi ERROR.
				CInstantiatedComponentsMembersDanger<SIZE>		MClassValue;
				int												MIntValue;
		};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! METHOD NEMA BODY, takze az do pouzitia METHOD C++ NEHODI ERROR, hoci priradenie INTEGER VALUE do CLASS v DEFAULT ARGUMENT je ERROR.
		void NoBody(CInstantiatedComponentsMembersSafe<TType> Value=3);

	public:
		void Test1(TType Value);
		void Test2(TType(*Pointer)[SIZE]);

	/*
	public:
		// !!!!! COMPILER hodi ERROR, pretoze CLASS [CInstantiatedComponentsMembersDanger] na ARRAY, ktory bude mat ZAPORNU DLZKU.
		// !!!!! VISUAL C++ HODI ERROR, ale GCC NEHODI.
		void TestError(TType Value);
	*/
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Ak je VALUE SIZE<=0, tak COMPILER hodi ERROR.
template<typename TType, int SIZE>
void CInstantiatedComponentsMembers<TType,SIZE>::Test1(TType Value)
{
	CInstantiatedComponentsMembersDanger<SIZE>					Object;

	for(int Index=0;Index<SIZE;Index++)
	{
		Object.SetArrayItem(Index,Value);
	}

	for(int Index=0;Index<SIZE;Index++)
	{
		TType													ArrayValue=Object.GetArrayItem(Index);

		std::wcout << L"TEST 1 - INDEX [" << Index << L"] VALUE [" << ArrayValue << L"]." << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
// !!! Ak je VALUE SIZE<=0, tak COMPILER hodi ERROR.
template<typename TType, int SIZE>
void CInstantiatedComponentsMembers<TType,SIZE>::Test2(TType(*Pointer)[SIZE])
{
	for(int Index=0;Index<SIZE;Index++)
	{
		TType													ArrayValue=(*Pointer)[Index];

		std::wcout << L"TEST 2 - INDEX [" << Index << L"] VALUE [" << ArrayValue << L"]." << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
/*
template<typename TType, int SIZE>
void CInstantiatedComponentsMembers<TType,SIZE>::TestError(TType Value)
{
	const int													SIZE=-1;

	// !!!!! COMPILER hodi ERROR, pretoze CLASS [CInstantiatedComponentsMembersDanger] na ARRAY, ktory bude mat ZAPORNU DLZKU.
	// !!!!! VISUAL C++ HODI ERROR, ale GCC NEHODI.
	CInstantiatedComponentsMembersDanger<SIZE>					Object;

	for(int Index=0;Index<SIZE;Index++)
	{
		Object.SetArrayItem(Index,Value);
	}

	for(int Index=0;Index<SIZE;Index++)
	{
		TType													ArrayValue=Object.GetArrayItem(Index);

		std::wcout << L"INDEX [" << Index << L"] VALUE [" << ArrayValue << L"]." << std::endl;
	}
}
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int SIZE>
int CInstantiatedComponentsMembers<TType,SIZE>::CInstantiatedComponentsMembersNested::GetArrayItem(int Index)
{
	if (Index<0 || Index>=SIZE)
	{
		throw(CException(L"ARRAY is OUT of BOUNDS."));
	}

	int															Value=MArray[Index];

	return(Value);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, int SIZE>
void CInstantiatedComponentsMembers<TType,SIZE>::CInstantiatedComponentsMembersNested::SetArrayItem(int Index, int Value)
{
	if (Index<0 || Index>=SIZE)
	{
		throw(CException(L"ARRAY is OUT of BOUNDS."));
	}

	MArray[Index]=Value;
}
//----------------------------------------------------------------------------------------------------------------------