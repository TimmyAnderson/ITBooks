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
// Trieda implementuje funkcnost pre Request-Reply Session - Sender.
//-------------------------------------------------------------------------------------------------------
	internal class CLCRequestSessionChannel : CLCRequestChannel, IRequestSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		// Zaroven ma uz session rozhranie.
		protected IRequestSessionChannel						MTypedInnerSessionChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCRequestSessionChannel(ChannelManagerBase ChannelManagerBase, IRequestSessionChannel InnerChannel, CLogData LogData)
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