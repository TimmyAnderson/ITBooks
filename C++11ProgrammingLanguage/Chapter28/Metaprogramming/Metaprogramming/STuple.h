//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
//-------------------------------------------------------------------------------------------------------
template<typename T1=void, typename T2=void, typename T3=void, typename T4=void>
struct STuple;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<>
struct STuple<>
{
//-------------------------------------------------------------------------------------------------------
	public:
		void Print(const wchar_t*, const wchar_t* Postfix)
		{
			if (Postfix!=nullptr)
			{
				std::wcout << Postfix;
			}
		}

	public:
		STuple(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<typename T1>
struct STuple<T1> : STuple<>
{
//-------------------------------------------------------------------------------------------------------
	public:
		T1														MValue;

	public:
		using BaseType=STuple<>;

	public:
		BaseType* GetBase(void)
		{
			BaseType*											Base=static_cast<BaseType*>(this);

			return(Base);
		}

		const BaseType* GetBase(void) const
		{
			const BaseType*										Base=static_cast<const BaseType*>(this);

			return(Base);
		}

		void Print(const wchar_t* Prefix, const wchar_t* Postfix)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << Prefix;
			}

			std::wcout << L"[" << MValue << L"]";

			// Vola METHOD Print() v BASE STRUCTURE.
			GetBase()->Print(nullptr,Postfix);
		}

	public:
		STuple(const T1& Value1)
			: BaseType(), MValue(Value1)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<typename T1, typename T2>
struct STuple<T1,T2> : STuple<T2>
{
//-------------------------------------------------------------------------------------------------------
	public:
		T1														MValue;

	public:
		using BaseType=STuple<T2>;

	public:
		BaseType* GetBase(void)
		{
			BaseType*											Base=static_cast<BaseType*>(this);

			return(Base);
		}

		const BaseType* GetBase(void) const
		{
			const BaseType*										Base=static_cast<const BaseType*>(this);

			return(Base);
		}

		void Print(const wchar_t* Prefix, const wchar_t* Postfix)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << Prefix;
			}

			std::wcout << L"[" << MValue << L"] ";

			// Vola METHOD Print() v BASE STRUCTURE.
			GetBase()->Print(nullptr,Postfix);
		}

	public:
		STuple(const T1& Value1, const T2& Value2)
			: BaseType(Value2), MValue(Value1)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<typename T1, typename T2, typename T3>
struct STuple<T1,T2,T3> : STuple<T2,T3>
{
//-------------------------------------------------------------------------------------------------------
	public:
		T1														MValue;

	public:
		using BaseType=STuple<T2,T3>;

	public:
		BaseType* GetBase(void)
		{
			BaseType*											Base=static_cast<BaseType*>(this);

			return(Base);
		}

		const BaseType* GetBase(void) const
		{
			const BaseType*										Base=static_cast<const BaseType*>(this);

			return(Base);
		}

		void Print(const wchar_t* Prefix, const wchar_t* Postfix)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << Prefix;
			}

			std::wcout << L"[" << MValue << L"] ";

			// Vola METHOD Print() v BASE STRUCTURE.
			GetBase()->Print(nullptr,Postfix);
		}

	public:
		STuple(const T1& Value1, const T2& Value2, const T3& Value3)
			: BaseType(Value2,Value3), MValue(Value1)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename T1, typename T2, typename T3, typename T4>
struct STuple : STuple<T2,T3,T4>
{
//-------------------------------------------------------------------------------------------------------
	public:
		T1														MValue;

	public:
		using BaseType=STuple<T2,T3,T4>;

	public:
		BaseType* GetBase(void)
		{
			BaseType*											Base=static_cast<BaseType*>(this);

			return(Base);
		}

		const BaseType* GetBase(void) const
		{
			const BaseType*										Base=static_cast<const BaseType*>(this);

			return(Base);
		}

		void Print(const wchar_t* Prefix, const wchar_t* Postfix)
		{
			if (Prefix!=nullptr)
			{
				std::wcout << Prefix;
			}

			std::wcout << L"[" << MValue << L"] ";

			// Vola METHOD Print() v BASE STRUCTURE.
			GetBase()->Print(nullptr,Postfix);
		}

	public:
		STuple(const T1& Value1, const T2& Value2, const T3& Value3, const T4& Value4)
			: BaseType(Value2,Value3,Value4), MValue(Value1)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Pomocna TEMPLATE, ktora sluzi na najdenie Nteho ITEM v TUPLE.
// !!! TEMPLATE vyuziva COMPILE-TIME REKURZIU.
template<typename TTypeToGet, int Index>
struct STupleItem
{
//-------------------------------------------------------------------------------------------------------
	public:
		template<typename TTupleType>
		static TTypeToGet& GetItem(TTupleType& TupleType)
		{
			return(STupleItem<TTypeToGet,Index-1>::GetItem(*TupleType.GetBase()));
		}

		template<typename TTupleType>
		static const TTypeToGet& GetItem(const TTupleType& TupleType)
		{
			return(STupleItem<TTypeToGet,Index-1>::GetItem(*TupleType.GetBase()));
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION, ktora sa aplikuje pre 0ty ITEM.
template<typename TTypeToGet>
struct STupleItem<TTypeToGet,0>
{
//-------------------------------------------------------------------------------------------------------
	public:
		template<typename TTupleType>
		static TTypeToGet& GetItem(TTupleType& TupleType)
		{
			return(TupleType.MValue);
		}

		template<typename TTupleType>
		static const TTypeToGet& GetItem(const TTupleType& TupleType)
		{
			return(TupleType.MValue);
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------