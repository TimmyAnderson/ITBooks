using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorChannelBase<TShape> : ChannelBase where TShape : class, IChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Referencia na dalsi kanal.
		private TShape											MInnerChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
    protected CDelegatorChannelBase(ChannelManagerBase ChannelManagerBase, TShape InnerChannel, string Source)
		: base(ChannelManagerBase) 
	{
        if (InnerChannel==null)
			throw(new ArgumentNullException("DelegatorChannelBase requires a non-null channel.", "InnerChannel"));

        // Set part of the String to print to console.
        MSource=string.Format("{0} CHANNEL STATE CHANGE: DelegatorChannelBase !", Source);
        // Set the reference to the next channel.
        MInnerChannel=InnerChannel;
    }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	protected TShape				InnerChannel
	{
		get
		{
			return(MInnerChannel);
		}
	}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override T GetProperty<T>()
		{
			return(this.MInnerChannel.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			CPrintHelper.Print(MSource, "OnAbort");
			this.MInnerChannel.Abort();
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "OnBeginClose");
			return(this.MInnerChannel.BeginClose(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "OnClose");
			this.MInnerChannel.Close(Timeout);
	    }
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndClose(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "OnEndClose");
			this.MInnerChannel.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CPrintHelper.Print(MSource, "OnBeginOpen");
			return(this.MInnerChannel.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CPrintHelper.Print(MSource, "OnOpen");
			this.MInnerChannel.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CPrintHelper.Print(MSource, "OnEndOpen");
			this.MInnerChannel.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------