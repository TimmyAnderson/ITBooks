using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorChannelFactory<TShape> : ChannelFactoryBase<TShape>
	{
//-------------------------------------------------------------------------------------------------------
		// Reference the next channel factory in the stack.
		private IChannelFactory<TShape>							MInnerFactory;
		// The String to print to the console.
		private string											MConsolePrefix="FACTORY: DelegatorChannelFactory";
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Ctor that builds the next channel factory in the stack, then assigns the MInnerFactory member variable calls the base ctor to set timeouts.
		public CDelegatorChannelFactory(BindingContext context) : base(context.Binding)
		{
			CPrintHelper.Print(MConsolePrefix, "ctor");
			this.MInnerFactory = context.BuildInnerChannelFactory<TShape>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Instantiates and returns a DelegatorChannel that references another channel.
		private TShape WrapChannel(TShape InnerChannel)
		{
			if(InnerChannel==null)
			{
				throw(new ArgumentNullException("innerChannel cannot be null !", "innerChannel"));
			}

			// Go through the channel shapes and return a wrapped channel
			if(typeof(TShape)==typeof(IOutputChannel))
				return((TShape)(object)new CDelegatorOutputChannel<IOutputChannel>(this, (IOutputChannel) InnerChannel, "SEND"));
			if(typeof(TShape) == typeof(IRequestChannel))
				return((TShape)(object)new CDelegatorRequestChannel(this, (IRequestChannel) InnerChannel, "SEND"));
			if(typeof(TShape) == typeof(IDuplexChannel))
				return((TShape)(object)new CDelegatorDuplexChannel(this, (IDuplexChannel) InnerChannel, "SEND"));
			if(typeof(TShape) == typeof(IOutputSessionChannel))
				return((TShape)(object)new CDelegatorOutputSessionChannel(this, (IOutputSessionChannel) InnerChannel, "SEND"));
			if(typeof(TShape) == typeof(IRequestSessionChannel))
				return((TShape)(object)new CDelegatorRequestSessionChannel(this, (IRequestSessionChannel) InnerChannel, "SEND"));
			if(typeof(TShape) == typeof(IDuplexSessionChannel))
				return((TShape)(object)new CDelegatorDuplexSessionChannel(this, (IDuplexSessionChannel) InnerChannel, "SEND"));

			throw(new ArgumentException(string.Format("Invalid channel shape passed: [{0}] !",InnerChannel.GetType())));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Uses the MInnerFactory member variable to build a channel then wraps it and returns the wrapped channel.
		protected override TShape OnCreateChannel(EndpointAddress Address, Uri Via)
		{
			// Create and return the channel.
			CPrintHelper.Print(MConsolePrefix, "OnCreateChannel");

			TShape				InnerChannel=this.MInnerFactory.CreateChannel(Address, Via);

			return(WrapChannel(InnerChannel));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MConsolePrefix, "OnBeginChannel");
			return(this.MInnerFactory.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CPrintHelper.Print(MConsolePrefix, "OnOpen");
			this.MInnerFactory.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CPrintHelper.Print(MConsolePrefix, "OnEndOpen");
			this.MInnerFactory.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			base.OnClose(Timeout);
			CPrintHelper.Print(MConsolePrefix, "OnClose");
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			base.OnAbort();
			CPrintHelper.Print(MConsolePrefix, "OnAbort");
		}
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>()
		{
			CPrintHelper.Print(MConsolePrefix, "GetProperty<" + typeof(T).Name + ">");
			return(this.MInnerFactory.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------