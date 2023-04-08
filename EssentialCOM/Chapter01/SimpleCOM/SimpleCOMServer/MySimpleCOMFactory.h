//------------------------------------------------------------------------------------------------------
#include <Unknwn.h>
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
class CMySimpleCOMFactory : public IClassFactory
{
//------------------------------------------------------------------------------------------------------
	private:
		volatile ULONG											MReferenceCounter;

	public:
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void **PPVObject);
		virtual ULONG STDMETHODCALLTYPE AddRef(void);
		virtual ULONG STDMETHODCALLTYPE Release(void);

        virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *PUnkOuter, REFIID RIID, void **PPVObject);
        virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL FLock);

	public:
		CMySimpleCOMFactory(void);
		virtual ~CMySimpleCOMFactory(void);
//------------------------------------------------------------------------------------------------------
};
//------------------------------------------------------------------------------------------------------