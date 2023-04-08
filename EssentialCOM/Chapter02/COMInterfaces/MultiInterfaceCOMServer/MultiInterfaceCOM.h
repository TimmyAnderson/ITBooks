//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "MultiInterfaceCOM_h.h"
//------------------------------------------------------------------------------------------------------
class CMultiInterfaceCOM : public IName, public IToString, public ITest, public IExceptionTest, public ISupportErrorInfo
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		CCriticalSectionWrapper									MCS;
		wchar_t*												MFirstName;
		wchar_t*												MLastName;
		int														MAge;
		bstr_t													MText;
		struct SName											MName;
		union UAge												MUnionAge;
		variant_t												MVariant;
		int														MProperty;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetFirstName(wchar_t* FirstName);
        virtual HRESULT STDMETHODCALLTYPE SetLastName(wchar_t* LastName);
        virtual HRESULT STDMETHODCALLTYPE SetAge(int Age);
        virtual HRESULT STDMETHODCALLTYPE GetFirstName(int BufferSize, wchar_t** FirstName);
        virtual HRESULT STDMETHODCALLTYPE GetLastName(int BufferSize, wchar_t** LastName);
        virtual HRESULT STDMETHODCALLTYPE GetAge(int* Age);

	public:
        virtual HRESULT STDMETHODCALLTYPE ToString(void);

	public:
        virtual HRESULT STDMETHODCALLTYPE SetString(BSTR Text);
        virtual HRESULT STDMETHODCALLTYPE GetString(BSTR* Text);
        virtual HRESULT STDMETHODCALLTYPE SetName(struct SName Name);
        virtual HRESULT STDMETHODCALLTYPE GetName(struct SName *Name);
        virtual HRESULT STDMETHODCALLTYPE SetUnion(int DiscriminatorField, union UAge Age);
        virtual HRESULT STDMETHODCALLTYPE GetUnion(int DiscriminatorField, union UAge *Age);
        virtual HRESULT STDMETHODCALLTYPE SetVariant(VARIANT Value);
        virtual HRESULT STDMETHODCALLTYPE GetVariant(VARIANT* Value);
        virtual HRESULT STDMETHODCALLTYPE Print1(IToString* Interface);
        virtual HRESULT STDMETHODCALLTYPE Print2(REFIID InterfaceID, IUnknown* Interface);
        virtual HRESULT STDMETHODCALLTYPE put_MyProperty(int Value);
        virtual HRESULT STDMETHODCALLTYPE get_MyProperty(int* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE ThrowException(boolean Throw);

	public:
        virtual HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(__RPC__in REFIID RIID);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CMultiInterfaceCOM(void);
		virtual ~CMultiInterfaceCOM(void);
};
//------------------------------------------------------------------------------------------------------