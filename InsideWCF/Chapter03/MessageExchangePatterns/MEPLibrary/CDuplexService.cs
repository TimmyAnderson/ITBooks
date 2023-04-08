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
	[ServiceBehavior(ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CDuplexService : IDuplexContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CDuplexService()
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SendMessage(Message SomeMessage)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("MESSAGE RECEIVED:\n{0}",SomeMessage.ToString());

			Message						MSG=CInsideWCFHelper.GenerateMessage("Jenny","Thompson",13);

			IDuplexCallbackContract		Callback=OperationContext.Current.GetCallbackChannel<IDuplexCallbackContract>();
			
			Callback.CallbackMessage(MSG);
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