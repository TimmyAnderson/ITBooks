//----------------------------------------------------------------------------------------------------------------------
export module MMyModule;
//----------------------------------------------------------------------------------------------------------------------
import <iostream>;
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyModuleNonExportFunction(void)
{
	wcout << L"NON EXPORT FUNCTION CALLED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
export void MyModuleFunction1(void)
{
	wcout << L"EXPORT FUNCTION 1 CALLED." << endl;

	MyModuleNonExportFunction();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
export
{
//----------------------------------------------------------------------------------------------------------------------
	void MyModuleFunction2(void)
	{
		wcout << L"EXPORT FUNCTION 2 CALLED." << endl;

		MyModuleNonExportFunction();
	}
//----------------------------------------------------------------------------------------------------------------------
	void MyModuleFunction3(void)
	{
		wcout << L"EXPORT FUNCTION 3 CALLED." << endl;

		MyModuleNonExportFunction();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CMyModuleClass final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			int													MValue;

		public:
			int GetValue(void) const noexcept;

		public:
			CMyModuleClass(int Value);
			virtual ~CMyModuleClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CMyModuleClass::CMyModuleClass(int Value)
		: MValue(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CMyModuleClass::~CMyModuleClass(void) noexcept
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int CMyModuleClass::GetValue(void) const noexcept
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------