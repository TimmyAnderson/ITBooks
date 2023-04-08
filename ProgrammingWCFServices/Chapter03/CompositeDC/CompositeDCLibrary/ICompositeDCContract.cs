using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace CompositeDCLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract()]
	public interface ICompositeDCContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CFriend GetFriend();
		[OperationContract]
		void SendFriend(CFriend Friend);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------