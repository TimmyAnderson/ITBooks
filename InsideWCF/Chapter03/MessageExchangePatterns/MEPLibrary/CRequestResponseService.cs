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
	[ServiceBehavior]
	public class CRequestResponseService : IRequestResponseContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CRequestResponseService()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public Message SendMessage(Message SomeMessage)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("MESSAGE RECEIVED:\n{0}",SomeMessage.ToString());

			CInsideWCFHelper.WriteMessageToConsole(SomeMessage.Headers.MessageId.ToString(),SomeMessage);

			Message					MSG=CInsideWCFHelper.GenerateMessage("Jenny","Thompson",13);

			return(MSG);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(CDebugHelper.GetDestructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------