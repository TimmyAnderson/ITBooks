using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace MessageHeadersHost
{
//-------------------------------------------------------------------------------------------------------
	public class CService2 : IService2
	{
//-------------------------------------------------------------------------------------------------------
		public void Operation2(ref string Message)
		{
			Console.WriteLine("CService2.Operation2() CALLED !");

			// Citam aktualny MessageHeader.
			CCustomHeaderData				Header=OperationContext.Current.IncomingMessageHeaders.GetHeader<CCustomHeaderData>("Operation2","NS");

			Console.WriteLine(string.Format("!!! OPERATION 2 - HEADER: [{0}] !",Header));

			Message+=" [Operation2]";
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------