using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessageContractLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IMessageContractContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void SomeDCOperation(CMyDataContract MyDataContract); 
		[OperationContract]
		void SomeMCOperation(CMyMessageContract MyMessageContract);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------