//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CPointersToMethodsBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MField;

	public:
		bool operator==(const CPointersToMethodsBase&) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::operator==() CALLED !" << std::endl;

			return(true);
		}

		bool operator!=(const CPointersToMethodsBase&) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::operator!=() CALLED !" << std::endl;

			return(true);
		}

	public:
		static void StaticMethod(void)
		{
			std::wcout << L"METHOD CPointersToMethodsBase::StaticMethod() CALLED !" << std::endl;
		}

		static void StaticMethod(const std::wstring& Value)
		{
			std::wcout << L"METHOD CPointersToMethodsBase::StaticMethod(" << Value << L") CALLED !" << std::endl;
		}

		static void StaticMethod(const std::wstring& Value1, int Value2)
		{
			std::wcout << L"METHOD CPointersToMethodsBase::StaticMethod(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

	private:
		void PrivateMethod(void)
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::PrivateMethod() CALLED !" << std::endl;
		}

	public:
		const std::wstring& GetField(void) const noexcept
		{
			return(MField);
		}

	public:
		void NonVirtualMethod1(void) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod1() CALLED !" << std::endl;
		}

		void NonVirtualMethod1(const std::wstring& Value) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod1(" << Value << L") CALLED !" << std::endl;
		}

		void NonVirtualMethod1(const std::wstring& Value1, int Value2) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod1(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

		void NonVirtualMethod2(void) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod2() CALLED !" << std::endl;
		}

		void NonVirtualMethod2(const std::wstring& Value) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod2(" << Value << L") CALLED !" << std::endl;
		}

		void NonVirtualMethod2(const std::wstring& Value1, int Value2) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::NonVirtualMethod2(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

	public:
		virtual void VirtualMethod1(void) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod1() CALLED !" << std::endl;
		}

		virtual void VirtualMethod1(const std::wstring& Value) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod1(" << Value << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod1(const std::wstring& Value1, int Value2) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod1(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(void) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod2() CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(const std::wstring& Value) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod2(" << Value << L") CALLED !" << std::endl;
		}

		virtual void VirtualMethod2(const std::wstring& Value1, int Value2) const
		{
			std::wcout << L"FIELD [" << MField << L"] - METHOD CPointersToMethodsBase::VirtualMethod2(" << Value1 << L"," << Value2 << L") CALLED !" << std::endl;
		}

	public:
		CPointersToMethodsBase(const std::wstring& Field)
			: MField(Field)
		{
		}

		virtual ~CPointersToMethodsBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------