//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <comdef.h>
#include "Helpers\CriticalSectionWrapper.h"
#include "CustomMarshalingByValueServer_h.h"
//------------------------------------------------------------------------------------------------------
class CCustomMarshalingByValueObject : public ICustomMarshalingByValueTest, public IMarshal
{
	private:
		volatile ULONG											MReferenceCounter;

	private:
		long													MValue;

	public:
        virtual HRESULT STDMETHODCALLTYPE SetValue(long Value);
        virtual HRESULT STDMETHODCALLTYPE GetValue(long* Value);

	public:
        virtual HRESULT STDMETHODCALLTYPE GetUnmarshalClass(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out CLSID* CID);
        virtual HRESULT STDMETHODCALLTYPE GetMarshalSizeMax(__in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags, __out DWORD* Size);
        virtual HRESULT STDMETHODCALLTYPE MarshalInterface(__in IStream* Stream, __in REFIID RIID, __in_opt void* PointerToObject, __in DWORD DestContext, __reserved void* ReservedDestContext, __in DWORD Flags);
        virtual HRESULT STDMETHODCALLTYPE UnmarshalInterface(__in IStream* Stream, __in REFIID RIID, __deref_out void** PointerToObject);
        virtual HRESULT STDMETHODCALLTYPE ReleaseMarshalData(__in IStream* Stream);
        virtual HRESULT STDMETHODCALLTYPE DisconnectObject(__in DWORD Reserved);

	public:
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, void** PointerToObject);
        virtual ULONG STDMETHODCALLTYPE AddRef(void);
        virtual ULONG STDMETHODCALLTYPE Release(void);

	public:
		CCustomMarshalingByValueObject(void);
		virtual ~CCustomMarshalingByValueObject(void);
};
//------------------------------------------------------------------------------------------------------