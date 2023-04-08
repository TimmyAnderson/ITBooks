using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IDCEquivalenceContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CServerPerson GetPerson();
		[OperationContract]
		void SendPerson(CServerPerson Person);
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		CServerErrorPerson GetErrorPerson();
		[OperationContract]
		void SendErrorPerson(CServerErrorPerson Person);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------