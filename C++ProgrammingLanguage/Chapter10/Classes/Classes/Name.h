//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CName
{
	private:
		std::wstring											MFirstName;
		std::wstring											MLastName;
		int														MAge;
		// !!! Pre CONST objekty tento FIELD NEBUDE OPTIMALIZOVANY a moze byt meneny i z CONST metod.
		mutable std::wstring									MMutableText;
		std::wstring											MNonMutableText;

	public:
		// MEMBER operator.
		bool operator==(CName& O);
		// !!! Operator== NEMOZE BYT STATIC operator.
		//static bool operator==(CName& O1, CName& O2);

	public:
		// Deklaracia STATICKEJ premennej.
		static CName											JENNY;

	public:
		std::wstring GetFirstName(void) const;
		void SetFirstName(std::wstring FirstName);

		std::wstring GetLastName(void) const;
		void SetLastName(std::wstring LastName);

		int GetAge(void) const;
		void SetAge(int Age);

	public:
		static void StaticPrintNameToConsole(CName& Name);

	public:
		void PrintNameToConsole(void) const;
		// !!! Metoda NEMOZE byt CONST kedze vola ine NON-CONST metody.
		//void SetAllFields(std::wstring FirstName, std::wstring LastName, int Age) const;
		void SetAllFields(std::wstring FirstName, std::wstring LastName, int Age);

	public:
		CName& ChainMethod1(void);
		CName& ChainMethod2(void);
		const CName& ConstChainMethod1(void) const;
		const CName& ConstChainMethod2(void) const;
		// !!! Objekt 'this' je v CONST metodach typu 'const CName*'.
		//CName& ConstChainMethodError(void) const;

	public:
		void NonConstSetMutableText(std::wstring Text);
		void ConstSetMutableText(std::wstring Text) const;
		void PrintMutableNonMutableTexts(std::wstring Prefix) const;

	public:
		// INLINE metoda definovava v TELE definicie CLASS.
		inline void Inline1(void){wprintf_s(L"Inline1() CALLED !\n");}
		// INLINE metoda definovana v .H subore, ale MIMO tela CLASS.
		inline void Inline2(void);
		// !!!!! LINKER ERROR. INLINE metoda NEMOZE byt definovana v CPP subore, pretoze KOMPILATOR by nemal pristupne v INYCH CPP FILES jej TELO a NEMOHOL by ho NAHRADIT na mieste volania INLINE METODY.
		inline void Inline3(void);

	public:
		CName(void);
		CName(std::wstring FirstName, std::wstring LastName, int Age);
		virtual ~CName(void);
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
inline void CName::Inline2(void)
{
	wprintf_s(L"Inline2() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------