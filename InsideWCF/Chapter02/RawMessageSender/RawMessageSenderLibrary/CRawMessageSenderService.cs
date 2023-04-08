using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace RawMessageSenderLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CRawMessageSenderService : IRawMessageSenderContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private bool											MToConsole=false;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CRawMessageSenderService()
		{
			Console.WriteLine(CDebugHelper.GetConstructorCallString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SubmitOrder(Message Order)
		{
			Console.WriteLine(CDebugHelper.GetMethodCallString());

			Console.WriteLine("Message ID {0} received !", Order.Headers.MessageId.ToString());

			// !!! Ak sa raz uz Message zapise nie je ju mozne znova zapisat. Inak povedane nemozem ju zapisat naraz do dvoch suborov, alebo do suboru a konzoly.
			if (MToConsole==false)
				CInsideWCFHelper.WriteServiceMessageToFile(Order.Headers.MessageId.ToString(),Order);
			else
				CInsideWCFHelper.WriteMessageToConsole(Order.Headers.MessageId.ToString(),Order);
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