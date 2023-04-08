//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <CorError.h>
#include "HostTaskManager.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostTaskManager::CHostTaskManager(void)
	: MReferenceCounter(0), MThreadMap(), MCLRTaskManager(NULL)
{
}
//------------------------------------------------------------------------------------------------------
CHostTaskManager::~CHostTaskManager(void)
{
	wprintf_s(L"!!!!!!!!!! HOST TASK MANAGER COM OBJECT DESTROYED !!!!!!!!!!\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::GetCurrentTask(IHostTask** Task)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::GetCurrentTask() CALLED !!!\n");

	HANDLE														CurrentThreadHandle=GetCurrentThread();
	CHostTask*													ExistingTask=MThreadMap[CurrentThreadHandle];

	if (ExistingTask!=NULL)
	{
		*Task=ExistingTask;

		return(S_OK);
	}
	else
	{
		CHostTask*												NewTask=new CHostTask(CurrentThreadHandle,GetCurrentThreadId());

		MThreadMap[GetCurrentThread()]=NewTask;
		NewTask->AddRef();

		*Task=NewTask;

		return(S_OK);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::CreateTask(DWORD StackSize, LPTHREAD_START_ROUTINE StartAddress, PVOID Parameter, IHostTask** Task)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::CreateTask() CALLED !!!\n");
	
	DWORD														ThreadID;
	HANDLE														ThreadHandle=(HANDLE) _beginthreadex(NULL,StackSize,(unsigned (__stdcall *) (void *))StartAddress,Parameter,CREATE_SUSPENDED,(unsigned int*) &ThreadID);
	CHostTask*													NewTask=new CHostTask(ThreadHandle,ThreadID);

	MThreadMap[ThreadHandle]=NewTask;

	*Task=NewTask;
	NewTask->AddRef();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::Sleep(DWORD Milliseconds, DWORD Option)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::Sleep() CALLED !!!\n");

	::Sleep(Milliseconds);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::SwitchToTask(DWORD Option)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::SwitchToTask() CALLED !!!\n");

	SwitchToThread();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::SetUILocale(LCID LocaleID)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::SetUILocale() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::SetLocale(LCID LocaleID)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::SetLocale() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::CallNeedsHostHook(SIZE_T Target, BOOL* CallNeedsHostHook)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::CallNeedsHostHook() CALLED !!!\n");

	*CallNeedsHostHook=FALSE;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::LeaveRuntime(SIZE_T Target)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::LeaveRuntime() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::EnterRuntime(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::EnterRuntime() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::ReverseLeaveRuntime(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::ReverseLeaveRuntime() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::ReverseEnterRuntime(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::ReverseEnterRuntime() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::BeginDelayAbort(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::BeginDelayAbort() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::EndDelayAbort(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::EndDelayAbort() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::BeginThreadAffinity(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::BeginThreadAffinity() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::EndThreadAffinity(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::EndThreadAffinity() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::SetStackGuarantee(ULONG Guarantee)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::SetStackGuarantee() CALLED !!!\n");

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::GetStackGuarantee(ULONG* Guarantee)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::GetStackGuarantee() CALLED !!!\n");

	*Guarantee=512*1024;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::SetCLRTaskManager(ICLRTaskManager* Manager)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTaskManager::SetCLRTaskManager() CALLED !!!\n");

	MCLRTaskManager=Manager;

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTaskManager::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostTaskManager*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostTaskManager*>(this);
		AddRef();
		return(S_OK);
	}
	else
	{
		*PointerToObject=NULL;
		return(E_NOINTERFACE);
	}
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostTaskManager::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostTaskManager::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------