//----------------------------------------------------------------------------------------------------------------------
// !!!!! POZOR. FILE musi mat nasledujuce nastavenia.
// !!! 1. FILE musi byt nastaveny ako C++ SOURCE FILE nastavenim OPTION [FILE CONTEXT MENU->Properties->Configuration Properties->General->Item Type] na VALUE [C/C++ compiler].
// !!! 2. FILE musi byt nastaveny ako INTERNAL PARITION MODULE FILE nastavenim OPTION [FILE CONTEXT MENU->Properties->Configuration Properties->C/C++->Advanced->Compile as] na VALUE [Compile as C++ Module Internal Partition (/internalPartition)]. Tato OPTION nastavi COMPILER OPTION [/internalPartition] pre dany FILE.
// !!!!! Alternativou je nastavenie na celom PROJECT nastavenim OPTIONS [Project->Properties->C/C++->General->Scan Sources for Module Dependencies] na VALUE [Yes].
//----------------------------------------------------------------------------------------------------------------------
module;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#include <string>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Deklaracia INTERNAL PARITION MODULE FILE.
module ModuleMultiFiles:File2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CMultiFileInternalClass2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CMultiFileInternalClass2(const std::wstring& Value);
		~CMultiFileInternalClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------