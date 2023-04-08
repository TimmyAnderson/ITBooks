using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace KnownTypesLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IKnownTypesContract
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