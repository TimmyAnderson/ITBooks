using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Pomocny enumerat vyuzivany metodou CAcceptChannelQueues.CheckSession().
*/
//-------------------------------------------------------------------------------------------------------
	internal enum ECheckSessionResponse
	{
//-------------------------------------------------------------------------------------------------------
		E_CSR_ERROR=0,
//-------------------------------------------------------------------------------------------------------
		E_CSR_NO_SESSION_REQUEST=1,
		E_CSR_NEW_SESSION=2,
		E_CSR_EXISTING_SESSION=3,
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------