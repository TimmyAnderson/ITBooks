using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace HelloWCFLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IHelloWCFContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void Say(string Input);
		[OperationContract]
		void SayWith2Params(string Input1, string Input2);
		[OperationContract]
		void SayPurchaseOrder(string SomeParam, CPurchaseOrder PO);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------