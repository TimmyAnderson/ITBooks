using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorInputSessionChannel : CDelegatorInputChannel<IInputSessionChannel>, IInputSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		private IInputSessionChannel							MInputSessionChannel;
		private string											MSource;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CDelegatorInputSessionChannel(ChannelManagerBase ChannelManagerBase, IInputSessionChannel InnerChannel, string Source)
			: base(ChannelManagerBase, InnerChannel, Source)
		{
			MSource=String.Format("{0} CHANNEL: DelegatorInputSessionChannel !", Source);
			CPrintHelper.Print(MSource, "ctor");
			this.MInputSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IInputSession									Session
		{
			get
			{
				CPrintHelper.Print(MSource, "Session");
				return(this.MInputSessionChannel.Session);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------