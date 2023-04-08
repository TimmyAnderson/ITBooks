using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorRequestChannel : CDelegatorChannelBase<IRequestChannel>, IRequestChannel
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorRequestChannel(ChannelManagerBase channelManagerBase, IRequestChannel innerChannel, String source)
			: base(channelManagerBase, innerChannel, source) {
			MSource = String.Format("{0} CHANNEL: DelegatorRequestChannel", source);
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
		public IAsyncResult BeginRequest(Message Message, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginRequest, no TimeSpan arg");
			return(this.BeginRequest(Message, this.DefaultSendTimeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginRequest(Message Message, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginRequest");
			return(this.InnerChannel.BeginRequest(Message, Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Request(Message Message)
		{
			CPrintHelper.Print(MSource, "Request (BLOCKING), no TimeSpan arg");
			return(this.Request(Message, this.DefaultSendTimeout));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Request(Message Message, TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "Request (BLOCKING)");

			Message				RetMessage=this.InnerChannel.Request(Message, Timeout);

			if (RetMessage == null)
				CPrintHelper.Print(MSource, "Request Returned no Message");
			else
				CPrintHelper.Print(MSource, "Request Returned a message");

			return(RetMessage);
		}
//-------------------------------------------------------------------------------------------------------
		public Message EndRequest(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndRequest");
			return(this.InnerChannel.EndRequest(Result));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------