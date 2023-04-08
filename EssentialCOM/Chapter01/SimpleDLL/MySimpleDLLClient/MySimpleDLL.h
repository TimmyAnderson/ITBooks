//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------------------------------------
class CExportedClass;
//------------------------------------------------------------------------------------------------------
extern __declspec(dllimport) int								MExportedVariable;
//------------------------------------------------------------------------------------------------------
void __declspec(dllimport) ExportedFunction(const CExportedClass& ExportedClass);
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
class __declspec(dllimport) CExportedClass
{
	private:
		wchar_t*												MText;

	public:
		const wchar_t* GetText(void) const;

	public:
		CExportedClass(const wchar_t* Text);
		~CExportedClass(void);
};
//------------------------------------------------------------------------------------------------------