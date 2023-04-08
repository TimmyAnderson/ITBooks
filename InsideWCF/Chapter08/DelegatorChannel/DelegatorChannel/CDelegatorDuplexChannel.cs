using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorDuplexChannel : CDelegatorInputChannel<IDuplexChannel>, IDuplexChannel
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorDuplexChannel(ChannelManagerBase ChannelManagerBase, IDuplexChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
	  
			MSource=string.Format("{0} CHANNEL: DelegatorDuplexChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									RemoteAddress
		{
			get
			{
				CPrintHelper.Print(MSource, "RemoteAddress");
				return(this.InnerChannel.RemoteAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public Uri												Via
		{
			get
			{
				CPrintHelper.Print(MSource, "Via");
				return(this.InnerChannel.Via);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginSend, no TimeSpan arg");
			return(this.BeginSend(Message, this.DefaultSendTimeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginSend");
			return(this.InnerChannel.BeginSend(Message, Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message)
		{
			CPrintHelper.Print(MSource, "Send, no TimeSpan arg");
			this.Send(Message, this.DefaultSendTimeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message, TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "Send");
			this.InnerChannel.Send(Message, Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSend(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndSend");
			this.InnerChannel.EndSend(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------