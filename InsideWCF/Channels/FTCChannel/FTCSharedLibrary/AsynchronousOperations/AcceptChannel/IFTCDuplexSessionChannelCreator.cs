using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Pomocne rozhranie sluziace ako factory k mojmu CH - CFTCDuplexChannel.
	Nemusel som to robit takto, cez facotry ale zdalo sa mi to elegantnejsie.
*/
//-------------------------------------------------------------------------------------------------------
	public interface IFTCDuplexSessionChannelCreator
	{
//-------------------------------------------------------------------------------------------------------
		// Vytvori CH na poziadanie.
		IDuplexSessionChannel CreateChannel(CFTCSessionID SessionID, Uri RemoteAddress);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------