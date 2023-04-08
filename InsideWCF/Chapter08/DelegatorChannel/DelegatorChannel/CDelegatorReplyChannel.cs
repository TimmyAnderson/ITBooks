using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorReplyChannel : CDelegatorChannelBase<IReplyChannel>, IReplyChannel
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorReplyChannel(ChannelManagerBase ChannelManagerBase, IReplyChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
		   
			MSource=String.Format("{0} CHANNEL: DelegatorReplyChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									LocalAddress
		{
			get
			{
				CPrintHelper.Print(MSource, "LocalAddress");
				return(this.InnerChannel.LocalAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceiveRequest(AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginReceiveRequest, no TimeSpan arg");
			return this.BeginReceiveRequest(this.DefaultReceiveTimeout, Callback, State);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceiveRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginReceiveRequest");
			return this.InnerChannel.BeginReceiveRequest(Timeout, Callback, State);
		}
//-------------------------------------------------------------------------------------------------------
		public RequestContext ReceiveRequest()
{
			CPrintHelper.Print(MSource, "ReceiveRequest, no TimeSpan arg");
			return this.ReceiveRequest(this.DefaultReceiveTimeout);
		}
//-------------------------------------------------------------------------------------------------------
		public RequestContext ReceiveRequest(TimeSpan Timeout)
{
			CPrintHelper.Print(MSource, "ReceiveRequest");
			return this.InnerChannel.ReceiveRequest(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public RequestContext EndReceiveRequest(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndReceiveRequest");
			return this.InnerChannel.EndReceiveRequest(Result);
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginTryReceiveRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginTryReceiveRequest");
			return this.InnerChannel.BeginTryReceiveRequest(Timeout, Callback, State);
		}
//-------------------------------------------------------------------------------------------------------
		public bool TryReceiveRequest(TimeSpan Timeout, out RequestContext Context)
		{
			CPrintHelper.Print(MSource, "TryReceiveRequest");
			return(this.InnerChannel.TryReceiveRequest(Timeout, out Context));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndTryReceiveRequest(IAsyncResult Result, out RequestContext Context)
		{
			CPrintHelper.Print(MSource, "EndTryReceiveRequest");
			return(this.InnerChannel.EndTryReceiveRequest(Result, out Context));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginWaitForRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginWaitForRequest");
			return(this.InnerChannel.BeginWaitForRequest(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool WaitForRequest(TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "WaitForRequest");
			return(this.InnerChannel.WaitForRequest(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndWaitForRequest(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndWaitForRequest");
			return(this.InnerChannel.EndWaitForRequest(Result));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------