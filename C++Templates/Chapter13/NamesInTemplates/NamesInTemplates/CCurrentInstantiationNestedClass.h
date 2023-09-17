//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE.
template<typename TType>
class CCurrentInstantiationNestedClassOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	using														MyType=TType;

	private:
		CString													MField;

	public:
		void Print(void) const;

	public:
		CCurrentInstantiationNestedClassOuter(const CString& Field);
		virtual ~CCurrentInstantiationNestedClassOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CCurrentInstantiationNestedClassInner1 final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MField;

		private:
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassOuter*				MField1;
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassOuter<MyType>*		MField2;
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassInner1*				MField3;

		public:
			const CCurrentInstantiationNestedClassOuter* GetField1(void) const noexcept;
			const CCurrentInstantiationNestedClassOuter<MyType>* GetField2(void) const noexcept;
			const CCurrentInstantiationNestedClassInner1* GetField3(void) const noexcept;

		public:
			void SetFields(CCurrentInstantiationNestedClassOuter* Field1, CCurrentInstantiationNestedClassOuter<MyType>* Field2, CCurrentInstantiationNestedClassInner1* Field3);

		public:
			void Print(void) const;

		public:
			CCurrentInstantiationNestedClassInner1(const CString& Field);
			virtual ~CCurrentInstantiationNestedClassInner1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CCurrentInstantiationNestedClassInner2 final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MField;

		private:
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassOuter*				MField1;
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassOuter<MyType>*		MField2;
			// !!! Toto je CURRENT INSTANTIATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassInner2*				MField3;
			// !!! Toto je UNKNOWN SPECIALIZATION INJECTED CLASS NAME.
			CCurrentInstantiationNestedClassInner1*				MField4;

		public:
			const CCurrentInstantiationNestedClassOuter* GetField1(void) const noexcept;
			const CCurrentInstantiationNestedClassOuter<MyType>* GetField2(void) const noexcept;
			const CCurrentInstantiationNestedClassInner2* GetField3(void) const noexcept;
			const CCurrentInstantiationNestedClassInner1* GetField4(void) const noexcept;

		public:
			void SetFields(CCurrentInstantiationNestedClassOuter* Field1, CCurrentInstantiationNestedClassOuter<MyType>* Field2, CCurrentInstantiationNestedClassInner2* Field3, CCurrentInstantiationNestedClassInner1* Field4);

		public:
			void Print(void) const;

		public:
			CCurrentInstantiationNestedClassInner2(const CString& Field);
			virtual ~CCurrentInstantiationNestedClassInner2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassOuter(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::~CCurrentInstantiationNestedClassOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationNestedClassOuter<TType>::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE [CCurrentInstantiationNestedClassOuter] - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::CCurrentInstantiationNestedClassInner1(const CString& Field)
	: MField(Field), MField1(), MField2(), MField3()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::~CCurrentInstantiationNestedClassInner1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationNestedClassOuter<TType>* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationNestedClassOuter<typename CCurrentInstantiationNestedClassOuter<TType>::MyType>* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const typename CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::GetField3(void) const noexcept
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::SetFields(CCurrentInstantiationNestedClassOuter* Field1, CCurrentInstantiationNestedClassOuter<MyType>* Field2, CCurrentInstantiationNestedClassInner1* Field3)
{
	MField1=Field1;
	MField2=Field2;
	MField3=Field3;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE [CCurrentInstantiationNestedClassInner1] - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::CCurrentInstantiationNestedClassInner2(const CString& Field)
	: MField(Field), MField1(), MField2(), MField3(), MField4()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::~CCurrentInstantiationNestedClassInner2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationNestedClassOuter<TType>* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const CCurrentInstantiationNestedClassOuter<typename CCurrentInstantiationNestedClassOuter<TType>::MyType>* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const typename CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::GetField3(void) const noexcept
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
const typename CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner1* CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::GetField4(void) const noexcept
{
	return(MField4);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::SetFields(CCurrentInstantiationNestedClassOuter* Field1, CCurrentInstantiationNestedClassOuter<MyType>* Field2, CCurrentInstantiationNestedClassInner2* Field3, CCurrentInstantiationNestedClassInner1* Field4)
{
	MField1=Field1;
	MField2=Field2;
	MField3=Field3;
	MField4=Field4;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CCurrentInstantiationNestedClassOuter<TType>::CCurrentInstantiationNestedClassInner2::Print(void) const
{
	std::wcout << L"PRIMARY TEMPLATE [CCurrentInstantiationNestedClassInner2] - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! FULL TEMPLATE SPECIALIZATION pre NESTED CLASS.
template<>
class CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CString													MField;

	public:
		void Print(void) const;

	public:
		CCurrentInstantiationNestedClassInner1(const CString& Field);
		virtual ~CCurrentInstantiationNestedClassInner1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner1::CCurrentInstantiationNestedClassInner1(const CString& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner1::~CCurrentInstantiationNestedClassInner1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCurrentInstantiationNestedClassOuter<int>::CCurrentInstantiationNestedClassInner1::Print(void) const
{
	std::wcout << L"FULL TEMPLATE SPECIALIZATION [CCurrentInstantiationNestedClassInner1] - FIELD [" << MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------