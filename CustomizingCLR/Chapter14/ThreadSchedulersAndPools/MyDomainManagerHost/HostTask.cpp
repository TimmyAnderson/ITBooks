//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <process.h>
#include <CorError.h>
#include "HostTask.h"
#include "Helpers\Lock.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "Helpers\Helpers.h"
//------------------------------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------------------------------
CHostTask::CHostTask(HANDLE ThreadHandle, DWORD ThreadID)
	: MReferenceCounter(0), MThreadHandle(ThreadHandle), MThreadID(ThreadID)
{
}
//------------------------------------------------------------------------------------------------------
CHostTask::~CHostTask(void)
{
	if (MThreadHandle!=0)
	{
		CloseHandle(MThreadHandle);
		MThreadHandle=0;
	}

	if (MCLRTask!=NULL)
	{
		MCLRTask->Release();
		MCLRTask=NULL;
	}

	wprintf_s(L"!!!!!!!!!! HOST TASK [%d] COM OBJECT DESTROYED !!!!!!!!!!\n",MThreadID);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::Start(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::Start() for TASK [%d] CALLED !!!\n",MThreadID);

	if (ResumeThread(MThreadHandle)!=-1)
	{
		return(S_OK);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::Alert(void)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::Alert() for TASK [%d] CALLED !!!\n",MThreadID);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::Join(DWORD Milliseconds, DWORD Option)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::Join() for TASK [%d] CALLED !!!\n",MThreadID);

	//MCLRTask->ExitTask();

	/*
	Sleep(5000);

	MCLRTask->ExitTask();

	Sleep(5000);
	*/

	BOOL														Alertable;

	if ((Option & WAIT_ALERTABLE)==WAIT_ALERTABLE)
	{
		Alertable=TRUE;
	}
	else
	{
		Alertable=FALSE;
	}

	DWORD														WaitResult=WaitForSingleObjectEx(MThreadHandle,Milliseconds,Alertable);

	if (WaitResult==WAIT_OBJECT_0)
	{
		wprintf_s(L"!!! CHostTask::Join() CLOSED TASK [%d] !!!\n",MThreadID);

		//Release();

		return(S_OK);
	}
	else if (WaitResult==WAIT_TIMEOUT)
	{
		/*
		MCLRTask->SwitchOut();
		MCLRTask->ExitTask();

		MCLRTask->Abort();
		MCLRTask->RudeAbort();
		*/

		wprintf_s(L"!!! CHostTask::Join() TERMINATED TASK [%d] !!!\n",MThreadID);

		// !!! Bohuzial sa mi NEPODARILO prinutit THREAD, aby sa KOREKTNE CHostTask::ThreadFunction() UKONCILA.
		TerminateThread(MThreadHandle,-1);

		return(HOST_E_TIMEOUT);
	}
	else
	{
		return(E_FAIL);
	}
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::SetPriority(int NewPriority)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::SetPriority() for TASK [%d] CALLED !!!\n",MThreadID);

	SetThreadPriority(MThreadHandle,NewPriority);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::GetPriority(int* Priority)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::GetPriority() for TASK [%d] CALLED !!!\n",MThreadID);

	*Priority=GetThreadPriority(MThreadHandle);

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::SetCLRTask(ICLRTask* CLRTask)
{
	CLock														Lock(MCS);

	wprintf_s(L"!!! CHostTask::SetCLRTask() for TASK [%d] CALLED !!!\n",MThreadID);

	MCLRTask=CLRTask;
	CLRTask->AddRef();

	return(S_OK);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
HRESULT STDMETHODCALLTYPE CHostTask::QueryInterface(REFIID RIID, void** PointerToObject)
{
	if (RIID==IID_IUnknown)
	{
		*PointerToObject=static_cast<IUnknown*>(static_cast<IHostTask*>(this));
		AddRef();
		return(S_OK);
	}
	else if (RIID==IID_IHostControl)
	{
		*PointerToObject=static_cast<IHostTask*>(this);
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
ULONG STDMETHODCALLTYPE CHostTask::AddRef(void)
{
	ULONG														Ret=InterlockedIncrement(&MReferenceCounter);

	return(Ret);
}
//------------------------------------------------------------------------------------------------------
ULONG STDMETHODCALLTYPE CHostTask::Release(void)
{
	ULONG														Ret=InterlockedDecrement(&MReferenceCounter);

	if (Ret==0)
	{
		delete(this);
	}

	return(Ret);
}
//------------------------------------------------------------------------------------------------------