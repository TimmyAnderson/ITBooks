using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace VersionRoundTripClient
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IVersionRoundTripContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CClientName DoRoundTripWithoutEDO(CClientName Name);
		[OperationContract]
		CClientName DoRoundTripWithEDO(CClientName Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------