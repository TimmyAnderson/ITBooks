using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace VersionRoundTripLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IVersionRoundTripContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CServerNameWithoutEDO DoRoundTripWithoutEDO(CServerNameWithoutEDO Name);
		[OperationContract]
		CServerNameWithEDO DoRoundTripWithEDO(CServerNameWithEDO Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------