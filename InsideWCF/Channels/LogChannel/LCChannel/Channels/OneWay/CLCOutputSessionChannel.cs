using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace LCChannel
{
//-------------------------------------------------------------------------------------------------------
// Trieda implementuje funkcnost pre OneWay Session - Sender.
//-------------------------------------------------------------------------------------------------------
	internal class CLCOutputSessionChannel : CLCOutputChannel, IOutputSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		// Zaroven ma uz session rozhranie.
		protected IOutputSessionChannel							MTypedInnerSessionChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCOutputSessionChannel(ChannelManagerBase ChannelManagerBase, IOutputSessionChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase, InnerChannel, LogData)
		{
			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MTypedInnerSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Pozor navratova hodnota je IOutputSession.
		public IOutputSession									Session
		{
			get
			{
				MLogData.WriteLog(CDebugHelper.GetMethodCallString());
				return(MTypedInnerSessionChannel.Session);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------