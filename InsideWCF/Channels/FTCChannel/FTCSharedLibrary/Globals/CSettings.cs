using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Staticka trieda obsahujuca globalne konstatny a nastavenia FTC CH.
	Nie vsetky sa pouzivaju.
*/
//-------------------------------------------------------------------------------------------------------
	public static class CSettings
	{
//-------------------------------------------------------------------------------------------------------
		// Log.
		private static CLog										MLog;
		// Typ serializacie a deserializacie M.
		private static ESOAPEncoder								MSOAPEncoder;
		// Maximalna dlzka headru M - NEPOUZIVA SA - mohla by sa pouzit v CFTCTransportBindingElement, kedze jej predok TransportBindingElement ma tuto property - ale nechal som ju na default.
		private static int										MMaxSizeOfMessageHeaders;
		// Maximalna dlzka Message - NEPOUZIVA SA - mohla by sa pouzit v CFTCTransportBindingElement, kedze jej predok TransportBindingElement ma tuto property - ale nechal som ju na default.
		private static int										MMaxSizeOfMessage;
		// Verzia M - je vyuzita pri serializacii a deserializacii Message - je to inak parameter konstruktora B - CFTCBinding.
		private static MessageVersion							MMessageVersion;
//-------------------------------------------------------------------------------------------------------
		// Maximlany cas na ukoncenie threadu TryReceive.
		private static int										MTryReceiveThreadExitTimeout;
		// Poll cas operacie TryReceive - ako casto sa kontroluje prichod novych pacektov (suborov) v adresari CH.
		private static int										MTryReceiveThreadCheckTimeout;
		// Maximlany cas na ukoncenie threadu AcceptChannel.
		private static int										MAcceptChannelThreadExitTimeout;
		// Poll cas operacie AcceptChannel - ako casto sa kontroluje prichod novych pacektov (suborov) v adresari CL.
		private static int										MAcceptChannelThreadCheckTimeout;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static CSettings()
		{
			// Tu sa nastavia hodnoty settings - uz sa nemenia.
			ELogRecordType					AllowedTypes=ELogRecordType.E_LRT_CHANNEL | ELogRecordType.E_LRT_EXCEPTION | ELogRecordType.E_LRT_SERVICE_CLIENT;

			MLog=new CLog(true,"FTC",@"..\..\..\..\Logs\FTCLog.txt",AllowedTypes);
			MSOAPEncoder=ESOAPEncoder.E_SE_TEXT;
			MMaxSizeOfMessageHeaders=65536;
			MMaxSizeOfMessage=1024*1024;
			MMessageVersion=MessageVersion.Soap12WSAddressing10;

			MTryReceiveThreadExitTimeout=10*1000;
			MTryReceiveThreadCheckTimeout=100;
			MAcceptChannelThreadExitTimeout=10*1000;
			MAcceptChannelThreadCheckTimeout=100;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public static CLog										Log
		{
			get
			{
				return(MLog);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static ESOAPEncoder								SOAPEncoder
		{
			get
			{
				return(MSOAPEncoder);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										MaxSizeOfMessageHeaders
		{
			get
			{
				return(MMaxSizeOfMessageHeaders);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										MaxSizeOfMessage
		{
			get
			{
				return(MMaxSizeOfMessage);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static MessageVersion							MessageVersion
		{
			get
			{
				return(MMessageVersion);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										TryReceiveThreadExitTimeout
		{
			get
			{
				return(MTryReceiveThreadExitTimeout);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										TryReceiveThreadCheckTimeout
		{
			get
			{
				return(MTryReceiveThreadCheckTimeout);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										AcceptChannelThreadExitTimeout
		{
			get
			{
				return(MAcceptChannelThreadExitTimeout);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public static int										AcceptChannelThreadCheckTimeout
		{
			get
			{
				return(MAcceptChannelThreadCheckTimeout);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------