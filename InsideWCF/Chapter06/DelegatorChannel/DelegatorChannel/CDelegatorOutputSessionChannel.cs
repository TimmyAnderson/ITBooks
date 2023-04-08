using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorOutputSessionChannel : CDelegatorOutputChannel<IOutputSessionChannel>, IOutputSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private IOutputSessionChannel							MInnerSessionChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorOutputSessionChannel(ChannelManagerBase ChannelManagerBase, IOutputSessionChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
	        
			MSource = String.Format("{0} CHANNEL: DelegatorOutputSessionChannel !", Source);
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