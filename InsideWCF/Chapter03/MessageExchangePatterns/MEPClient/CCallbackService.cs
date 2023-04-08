using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MEPLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MEPClient
{
//-------------------------------------------------------------------------------------------------------
	public class CCallbackService : IDuplexCallbackContract
	{
//-------------------------------------------------------------------------------------------------------
		public void CallbackMessage(Message SomeMessage)
		{
			Console.WriteLine("\n\n\nCALLBACK MESSAGE RECEIVED:\n{0}",SomeMessage.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------