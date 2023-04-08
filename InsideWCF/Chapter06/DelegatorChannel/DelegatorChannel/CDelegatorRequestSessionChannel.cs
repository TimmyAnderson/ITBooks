using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorRequestSessionChannel : CDelegatorRequestChannel, IRequestSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private IRequestSessionChannel							MInnerSessionChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorRequestSessionChannel(ChannelManagerBase ChannelManagerBase, IRequestSessionChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
	 
			MSource=string.Format("{0} CHANNEL: DelegatorRequestSessionChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
			this.MInnerSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IOutputSession									Session
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