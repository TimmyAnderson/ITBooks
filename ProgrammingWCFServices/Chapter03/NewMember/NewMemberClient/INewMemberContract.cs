using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace NewMemberClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface INewMemberContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CClientName GetName();
		[OperationContract]
		void SendName(CClientName Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------