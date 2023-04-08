using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Xml;
//-------------------------------------------------------------------------------------------------------
namespace CustomHeadersInConfigHost
{
//-------------------------------------------------------------------------------------------------------
	public class CService : IService
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpperEndpointHeader(string Value)
		{
			Console.WriteLine("ToUpper() CALLED !");

			int						Position=-1;
			int						Counter=0;

			foreach (MessageHeaderInfo MHI in OperationContext.Current.IncomingMessageHeaders)
			{
				if (MHI.Name=="XXX")
					Position=Counter;

				Console.WriteLine(string.Format("\t{0}. Header: {1} !",++Counter,MHI.Name));
			}

			try
			{
				if (Position>0)
				{
					using (XmlDictionaryReader Reader=OperationContext.Current.IncomingMessageHeaders.GetReaderAtHeader(Position))
					{
						string			Context=Reader.ReadOuterXml();

						Console.WriteLine(string.Format("XML Context:\n[\n{0}\n]",Context));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
		public string ToUpperAddressHeader(string Value)
		{
			Console.WriteLine("ToUpper() CALLED !");

			int						Position=-1;
			int						Counter=0;

			foreach (MessageHeaderInfo MHI in OperationContext.Current.IncomingMessageHeaders)
			{
				if (MHI.Name=="MyAddressHeader")
					Position=Counter;

				Console.WriteLine(string.Format("\t{0}. Header: {1} !",++Counter,MHI.Name));
			}

			try
			{
				if (Position>0)
				{
					using (XmlDictionaryReader Reader=OperationContext.Current.IncomingMessageHeaders.GetReaderAtHeader(Position))
					{
						string			Context=Reader.ReadOuterXml();

						Console.WriteLine(string.Format("XML Context:\n[\n{0}\n]",Context));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------