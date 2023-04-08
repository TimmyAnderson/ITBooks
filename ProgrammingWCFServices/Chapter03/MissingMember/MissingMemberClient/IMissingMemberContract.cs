using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace MissingMemberClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IMissingMemberContract
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