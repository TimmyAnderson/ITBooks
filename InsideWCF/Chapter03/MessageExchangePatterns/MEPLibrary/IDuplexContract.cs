using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MEPLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(Namespace="http://wintellect.com/",CallbackContract=typeof(IDuplexCallbackContract))]
	public interface IDuplexContract
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract(Action="*")]
		void SendMessage(Message SomeMessage);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------