using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorReplySessionChannel : CDelegatorReplyChannel, IReplySessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private IReplySessionChannel							MInnerSessionChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorReplySessionChannel(ChannelManagerBase ChannelManagerBase, IReplySessionChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
			MSource = String.Format("{0} CHANNEL: DelegatorReplySessionChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
			this.MInnerSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IInputSession									Session
		{
			get
			{
				CPrintHelper.Print(MSource, "Session");
				return(this.MInnerSessionChannel.Session);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------