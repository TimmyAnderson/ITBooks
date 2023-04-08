using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.Runtime.Serialization;
//-------------------------------------------------------------------------------------------------------
namespace ServiceKnownTypesLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IServiceKnownTypesContract
	{
//-------------------------------------------------------------------------------------------------------
		// Tato operacia akceptuje CName aj CFullName.
		[OperationContract]
		[ServiceKnownType(typeof(CFullName))]
		CName GetName();
		// Tato operacia akceptuje iba CName.
		[OperationContract]
		void SendJustName(CName Name);
		// Tato operacia akceptuje CName aj CFullName.
		[OperationContract]
		[ServiceKnownType(typeof(CFullName))]
		void SendAllNameTypes(CName Name);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------