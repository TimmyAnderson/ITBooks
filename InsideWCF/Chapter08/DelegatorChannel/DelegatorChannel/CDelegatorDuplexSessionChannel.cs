using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorDuplexSessionChannel : CDelegatorDuplexChannel, IDuplexSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private IDuplexSessionChannel							MInnerSessionChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorDuplexSessionChannel(ChannelManagerBase ChannelManagerBase, IDuplexSessionChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
			MSource=string.Format("{0} CHANNEL: DelegatorDuplexSessionChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
			this.MInnerSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IDuplexSession									Session
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