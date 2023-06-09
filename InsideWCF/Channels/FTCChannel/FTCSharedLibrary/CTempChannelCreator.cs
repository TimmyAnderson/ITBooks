using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	internal class CTempChannelCreator : IFTCDuplexSessionChannelCreator
	{
//-------------------------------------------------------------------------------------------------------
		private CChannelAcceptChannelThread	MChannelAcceptChannelThread;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTempChannelCreator(CChannelAcceptChannelThread ChannelAcceptChannelThread)
		{
			MChannelAcceptChannelThread=ChannelAcceptChannelThread;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public IDuplexSessionChannel CreateChannel(CFTCSessionID SessionID, Uri RemoteAddress)
		{
			CTempChannel		Ret=new CTempChannel(SessionID,MChannelAcceptChannelThread);

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------