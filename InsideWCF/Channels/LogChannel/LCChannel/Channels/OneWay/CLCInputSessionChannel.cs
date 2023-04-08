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
// Trieda implementuje funkcnost pre OneWay Session - Receiver.
//-------------------------------------------------------------------------------------------------------
	internal class CLCInputSessionChannel : CLCInputChannel, IInputSessionChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		// Zaroven ma uz session rozhranie.
		protected IInputSessionChannel							MTypedInnerSessionChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCInputSessionChannel(ChannelManagerBase ChannelManagerBase, IInputSessionChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase, InnerChannel, LogData)
		{
			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MTypedInnerSessionChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Pozor navratova hodnota je IInputSession.
		public IInputSession									Session
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