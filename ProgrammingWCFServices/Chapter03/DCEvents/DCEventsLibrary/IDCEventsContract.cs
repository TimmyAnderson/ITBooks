using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DCEventsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IDCEventsContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CName GetName();
		[OperationContract]
		void SendName(CName Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------