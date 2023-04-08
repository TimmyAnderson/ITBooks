//------------------------------------------------------------------------------------------------------
#include <Unknwn.h>
#include <comdef.h>
//------------------------------------------------------------------------------------------------------
class CAsynchronousMethodsObjectFactory : public IClassFactory
{
	private:
		volatile ULONG											MReferenceCounter;

	public:
        virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* UnkOuter, REFIID RIID, void** PointerToObject);
        virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL Lock);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CAsynchronousMethodsObjectFactory(void);
		virtual ~CAsynchronousMethodsObjectFactory(void);
};
//------------------------------------------------------------------------------------------------------