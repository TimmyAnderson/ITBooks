using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorChannelListener<TShape> : ChannelListenerBase<TShape> where TShape : class, IChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Reference to tne next channel listener in the stack.
		private IChannelListener<TShape>						MInnerListener;
		// The string to print to the console.
		private string											MConsolePrefix="LISTENER: DelegatorChannelListener";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Build the next channel listener, then refer to it calls the base ctor to set timeouts.
		public CDelegatorChannelListener(BindingContext Context)
			: base(Context.Binding)
		{
			this.MInnerListener=Context.BuildInnerChannelListener<TShape>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override Uri										Uri
		{
			get
			{
				CPrintHelper.Print(MConsolePrefix, "Uri");
				return(this.MInnerListener.Uri); 
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Instantiates and returns a DelegatorChannel that references another channel.
		private TShape WrapChannel(TShape InnerChannel)
		{
			if(InnerChannel==null)
				throw(new ArgumentNullException("InnerChannel cannot be null !", "InnerChannel"));

			// Go through the channel shapes and return a wrapped channel.
			if(typeof(TShape) == typeof(IInputChannel))
				return((TShape)(object)new CDelegatorInputChannel<IInputChannel>(this, (IInputChannel) InnerChannel, "RECEIVE"));
			if (typeof(TShape) == typeof(IReplyChannel))
				return((TShape)(object)new CDelegatorReplyChannel(this, (IReplyChannel) InnerChannel, "RECEIVE"));
			if (typeof(TShape) == typeof(IDuplexChannel))
				return((TShape)(object)new CDelegatorDuplexChannel(this, (IDuplexChannel) InnerChannel, "RECEIVE"));
			if (typeof(TShape) == typeof(IInputSessionChannel))
				return((TShape)(object)new CDelegatorInputSessionChannel(this, (IInputSessionChannel) InnerChannel, "RECEIVE"));
			if (typeof(TShape) == typeof(IReplySessionChannel))
				return((TShape)(object)new CDelegatorReplySessionChannel(this, (IReplySessionChannel) InnerChannel, "RECEIVE"));
			if (typeof(TShape) == typeof(IDuplexSessionChannel))
				return((TShape)(object)new CDelegatorDuplexSessionChannel(this, (IDuplexSessionChannel) InnerChannel, "RECEIVE"));

			// Cannot wrap this channel.
			throw(new ArgumentException(String.Format("Invalid channel shape passed: {0} !", InnerChannel.GetType())));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginAcceptChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginAcceptChannel");
			return(this.MInnerListener.BeginAcceptChannel(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override TShape OnAcceptChannel(TimeSpan Timeout)
		{
			// Create and return the channel.
			CPrintHelper.Print(MConsolePrefix, "OnAcceptChannel");

			TShape				InnerChannel=MInnerListener.AcceptChannel(Timeout);
		    
			// When shutting down, the InnerChannel can be null.
			if (InnerChannel!=null)
				return(WrapChannel(InnerChannel));

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		protected override TShape OnEndAcceptChannel(IAsyncResult Result)
		{
			// Create and return the channel.
			CPrintHelper.Print(MConsolePrefix, "OnEndAcceptChannel");

			TShape				InnerChannel=MInnerListener.EndAcceptChannel(Result);

			// When closing, MInner.EndAcceptChannel returns null, nothing to wrap.
			if (InnerChannel!=null)
				return(WrapChannel(InnerChannel));

			return(null);
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginWaitForChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginWaitForChannel");
			return(this.MInnerListener.BeginWaitForChannel(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override bool OnWaitForChannel(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnWaitForChannel");
			return(this.MInnerListener.WaitForChannel(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		protected override bool OnEndWaitForChannel(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndWaitForChannel");
			return(this.MInnerListener.EndWaitForChannel(Result));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			CPrintHelper.Print(MConsolePrefix, "OnAbort");
			this.MInnerListener.Abort();
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginOpen");
			return(this.MInnerListener.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnOpen");
			this.MInnerListener.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndOpen");
			this.MInnerListener.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginClose");
			return(this.MInnerListener.BeginClose(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnClose");
			this.MInnerListener.Close(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndClose(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndClose");
			this.MInnerListener.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>()
		{
			CPrintHelper.Print(MConsolePrefix, "GetProperty<" + typeof(T) + ">");
			return(this.MInnerListener.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------