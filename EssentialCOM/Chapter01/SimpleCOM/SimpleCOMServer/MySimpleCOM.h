//------------------------------------------------------------------------------------------------------
#include <Unknwn.h>
#include <comdef.h>
#include "IMySimpleInterface.h"
//------------------------------------------------------------------------------------------------------
class CMySimpleCOM : public IMySimpleInterface
{
//------------------------------------------------------------------------------------------------------
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CRITICAL_SECTION										MCS;
		int														MIntValue;
		_bstr_t													MStringValue;

	public:
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void **PPVObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);

		virtual HRESULT GetInt(int* Value);
		virtual HRESULT SetInt(int Value);
		virtual HRESULT GetString(BSTR* Value);
		virtual HRESULT SetString(BSTR Value);

	public:
		CMySimpleCOM(void);
		virtual ~CMySimpleCOM(void);
//------------------------------------------------------------------------------------------------------
};
//------------------------------------------------------------------------------------------------------