using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Pomocna trieda sluziaca ako class factory pre moj CH - CFTCDuplexChannel.
*/
//-------------------------------------------------------------------------------------------------------
	internal class CFTCDuplexChannelCreator : IFTCDuplexSessionChannelCreator
	{
//-------------------------------------------------------------------------------------------------------
		private ChannelManagerBase								MCMB;
		private bool											MIsListener;
		private Uri												MLocalAddress;
		private MessageEncoder									MMessageEncoder;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCDuplexChannelCreator(ChannelManagerBase CMB, bool IsListener, Uri LocalAddress, MessageEncoder MessageEncoder)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MCMB=CMB;
			MIsListener=IsListener;
			MLocalAddress=LocalAddress;
			MMessageEncoder=MessageEncoder;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IDuplexSessionChannel CreateChannel(CFTCSessionID SessionID, Uri RemoteAddress)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			return(new CFTCDuplexChannel(MCMB,SessionID,MIsListener,MLocalAddress,RemoteAddress,MMessageEncoder));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------