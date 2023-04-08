using System;
using System.Collections.Generic;
using System.Text;
using System.Messaging;
//-------------------------------------------------------------------------------------------------------
namespace PlaybackFailuresClient
{
//-------------------------------------------------------------------------------------------------------
	public class CMSMQHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static string VerifyQueue(string Name)
		{
			string		QueueName=@".\private$\" + Name;
			string		EndpointName=@"net.msmq://localhost/private/" + Name;

			if(MessageQueue.Exists(QueueName)==false)
			   MessageQueue.Create(QueueName,true);

			return(EndpointName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------