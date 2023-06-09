//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
class __declspec(dllexport) CExportedClass;
//------------------------------------------------------------------------------------------------------
extern __declspec(dllexport) int								MExportedVariable;
//------------------------------------------------------------------------------------------------------
__declspec(dllexport) void ExportedFunction(const CExportedClass& ExportedClass);
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
class __declspec(dllexport) CExportedClass
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