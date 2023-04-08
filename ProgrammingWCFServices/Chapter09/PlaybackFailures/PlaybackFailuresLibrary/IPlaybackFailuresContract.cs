using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PlaybackFailuresLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed)]
	public interface IPlaybackFailuresContract
	{
//-------------------------------------------------------------------------------------------------------
        [OperationContract(IsOneWay=true)]
		void PrintText(string Message);
        [OperationContract(IsOneWay=true)]
		void ThrowExceptionWithTransaction1(string Message);
        [OperationContract(IsOneWay=true)]
		void ThrowExceptionWithTransaction2(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------