//----------------------------------------------------------------------------------------------------------------------
#include "CTimerGlobal.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
VOID CTimerGlobal::StaticTimerCallbackMethod(PEX_TIMER Timer, PVOID Context)
{
	UNREFERENCED_PARAMETER(Timer);

	CTimerGlobal*												This=static_cast<CTimerGlobal*>(Context);

	This->TimerCallbackMethod();
}
//----------------------------------------------------------------------------------------------------------------------
VOID CTimerGlobal::StaticDeleteTimerCallbackMethod(PVOID Context)
{
	CTimerGlobal*												This=static_cast<CTimerGlobal*>(Context);

	This->TimerDeleteCallbackMethod();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
VOID CTimerGlobal::TimerCallbackMethod(void)
{
	MTimerCallback(MCallbackData);
}
//----------------------------------------------------------------------------------------------------------------------
VOID CTimerGlobal::TimerDeleteCallbackMethod(void)
{
	MTimerDeleteCallback(MCallbackData);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
PEX_TIMER CTimerGlobal::GetTimer(void)
{
	return(MTimer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
BOOLEAN CTimerGlobal::SetTimer(LONGLONG DueTime, LONGLONG Period, LONGLONG NoWakeTolerance)
{
	EXT_SET_PARAMETERS											SetTimerParameters;

	ExInitializeSetTimerParameters(&SetTimerParameters);

	SetTimerParameters.NoWakeTolerance=NoWakeTolerance;

	BOOLEAN														TimerCancelledInSetTime=ExSetTimer(MTimer,DueTime,Period,&SetTimerParameters);

	return(TimerCancelledInSetTime);
}
//----------------------------------------------------------------------------------------------------------------------
BOOLEAN CTimerGlobal::CancelTimer(void)
{
	BOOLEAN														TimerCancelledInCancel=ExCancelTimer(MTimer,nullptr);

	return(TimerCancelledInCancel);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
BOOLEAN CTimerGlobal::Init(TypeTimerCallback* TimerCallback, TypeTimerDeleteCallback* TimerDeleteCallback, ETimerAttributes Attributes, PVOID CallbackData)
{
	MTimer=ExAllocateTimer(StaticTimerCallbackMethod,this,static_cast<ULONG>(Attributes));

	if (MTimer!=nullptr)
	{
		MTimerCallback=TimerCallback;
		MTimerDeleteCallback=TimerDeleteCallback;
		MCallbackData=CallbackData;

		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}
//----------------------------------------------------------------------------------------------------------------------
BOOLEAN CTimerGlobal::Destroy(BOOLEAN Cancel, BOOLEAN Wait)
{
	EXT_DELETE_PARAMETERS										DeleteParameters;

	ExInitializeDeleteTimerParameters(&DeleteParameters);

	DeleteParameters.DeleteCallback=StaticDeleteTimerCallbackMethod;
	DeleteParameters.DeleteContext=this;

	BOOLEAN														TimerCancelledInDelete=ExDeleteTimer(MTimer,Cancel,Wait,&DeleteParameters);

	return(TimerCancelledInDelete);
}
//----------------------------------------------------------------------------------------------------------------------