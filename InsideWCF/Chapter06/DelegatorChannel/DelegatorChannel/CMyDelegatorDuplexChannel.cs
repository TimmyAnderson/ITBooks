using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
// Type that can be used directly, but must be used with the IDuplexSessionChannel shape the other channel examples show how to build a type hierarchy for multiple channel shapes.
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CMyDelegatorDuplexChannel : ChannelBase, IDuplexSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Reference the next channel in the channel stack.
		private IDuplexSessionChannel							MInnerChannel;
		private string											MConsolePrefix;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CMyDelegatorDuplexChannel(ChannelManagerBase ChannelManagerBase, IDuplexSessionChannel InnerChannel, string ConsolePrefix)
			: base(ChannelManagerBase)
		{
			MInnerChannel=InnerChannel;
			MConsolePrefix=ConsolePrefix;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									LocalAddress
		{
			get
			{
				CPrintHelper.Print(MConsolePrefix, "LocalAddress");
				return(MInnerChannel.LocalAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									RemoteAddress
		{
			get
			{
				CPrintHelper.Print(MConsolePrefix, "RemoteAddress");
				return(MInnerChannel.RemoteAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public Uri												Via
		{
			get
			{
				CPrintHelper.Print(MConsolePrefix, "Via");
				return(MInnerChannel.Via);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public IDuplexSession									Session
		{
			get
			{
				CPrintHelper.Print(MConsolePrefix, "Session");
				return(MInnerChannel.Session);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginReceive");
			return(MInnerChannel.BeginReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive()
		{
			CPrintHelper.Print(MConsolePrefix, "Receive, no TimeSpan arg");
			return(this.Receive(this.DefaultReceiveTimeout));
		}
//-------------------------------------------------------------------------------------------------------
		public Message Receive(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "Receive");
			return(MInnerChannel.Receive(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginReceive(AsyncCallback callback, object state)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginReceive");
			return(MInnerChannel.BeginReceive(callback, state));
		}
//-------------------------------------------------------------------------------------------------------
		public Message EndReceive(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "EndReceive");
			return(MInnerChannel.EndReceive(Result));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginTryReceive");
			return(MInnerChannel.BeginTryReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool TryReceive(TimeSpan Timeout, out Message Message)
		{
			CPrintHelper.Print(MConsolePrefix, "TryReceive");
			return(MInnerChannel.TryReceive(Timeout, out Message));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			CPrintHelper.Print(MConsolePrefix, "EndTryReceive");
			return(MInnerChannel.EndTryReceive(Result, out Message));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginWaitForMessage(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginWaitForMessage");
			return(MInnerChannel.BeginWaitForMessage(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public bool WaitForMessage(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "WaitForMessage");
			return(MInnerChannel.WaitForMessage(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		public bool EndWaitForMessage(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "EndWaitForMessage");
			return(MInnerChannel.EndWaitForMessage(Result));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginSend");
			return(MInnerChannel.BeginSend(Message, Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		public IAsyncResult BeginSend(Message Message, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "BeginSend, no TimeSpan arg");
			return this.BeginSend(Message, this.DefaultSendTimeout, Callback, State);
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message)
		{
			CPrintHelper.Print(MConsolePrefix, "Send, no TimeSpan arg");
			this.Send(Message, this.DefaultSendTimeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void Send(Message Message, TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "Send");
			MInnerChannel.Send(Message, Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		public void EndSend(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "EndSend");
			MInnerChannel.EndSend(Result);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			CPrintHelper.Print(MConsolePrefix, "OnAbort");
			MInnerChannel.Abort();
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginOpen");
			return(MInnerChannel.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnOpen");
			MInnerChannel.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndOpen");
			MInnerChannel.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginClose");
			return(MInnerChannel.BeginClose(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnClose");
			MInnerChannel.Close(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndClose(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndClose");
			MInnerChannel.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>()
		{
			return(MInnerChannel.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------