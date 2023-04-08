using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace RequiredMemberClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IRequiredMemberContract
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