using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorInputChannel<TShape> : CDelegatorChannelBase<TShape>, IInputChannel where TShape:class, IInputChannel
	{
//-------------------------------------------------------------------------------------------------------
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorInputChannel(ChannelManagerBase ChannelManagerBase, TShape InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
			// Assign the name and generic parameter to the String.
			MSource=string.Format("{0} CHANNEL: DelegatorInputChannel<{1}> !", Source, typeof(TShape).Name);
			// Output that the method was called.
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
		public IAsyncResult BeginReceive(AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginReceive, no TimeSpan arg");
			return(this.BeginReceive(this.DefaultReceiveTimeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginReceive");
			return(this.InnerChannel.BeginReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive()
		{
			CPrintHelper.Print(MSource, "Receive, no TimeSpan arg");
			return(this.Receive(this.DefaultReceiveTimeout));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive(TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "Receive");
			return(this.InnerChannel.Receive(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		public Message EndReceive(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndReceive");
			return(this.InnerChannel.EndReceive(Result));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginTryReceive");
			return(this.InnerChannel.BeginTryReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool TryReceive(TimeSpan Timeout, out Message Message)
		{
			CPrintHelper.Print(MSource, "TryReceive (BLOCKING)");

			bool			MessageReceived=this.InnerChannel.TryReceive(Timeout, out Message);
		    
			if (MessageReceived==false)
				CPrintHelper.Print(MSource, "TryReceive Returned no Message");

			if (MessageReceived==true && Message==null)
				CPrintHelper.Print(MSource, "TryReceive Returned true, but no message");

			if (MessageReceived==true && Message!=null)
				CPrintHelper.Print(MSource, "TryReceive Returned true and a message");

			return(MessageReceived);
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			CPrintHelper.Print(MSource, "EndTryReceive");
			return(this.InnerChannel.EndTryReceive(Result, out Message));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginWaitForMessage(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "BeginWaitForMessage");
			return(this.InnerChannel.BeginWaitForMessage(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool WaitForMessage(TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "WaitForMessage");
			return(this.InnerChannel.WaitForMessage(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndWaitForMessage(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "EndWaitForMessage");
			return(this.InnerChannel.EndWaitForMessage(Result));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------