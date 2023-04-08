using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.ServiceModel;
using System.ServiceModel.Channels;
using StreamingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace StreamingClient
{
//-------------------------------------------------------------------------------------------------------
	public class CStreamingProxy : ClientBase<IStreamingContract>, IStreamingContract
	{
//-------------------------------------------------------------------------------------------------------
		public CStreamingProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SendStream(Stream Message)
		{
			Console.WriteLine("CStreamingProxy.SendStream() !");
			Channel.SendStream(Message);
		}
//-------------------------------------------------------------------------------------------------------
		public Stream ReceiveStream()
		{
			Console.WriteLine("CStreamingProxy.ReceiveStream() !");
			return(Channel.ReceiveStream());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------