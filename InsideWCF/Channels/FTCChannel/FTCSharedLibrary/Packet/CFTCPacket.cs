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
	Reprezentuje packet, teda prenosovu jednotku, ktora sa pomocou suboru na disku prenasa medzi Sender a Receiver.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCPacket
	{
//-------------------------------------------------------------------------------------------------------
		// Cas vytvorenia packetu.
		private DateTime										MDateTime;
		// SessionID session do ktoreho je packet urceny.
		private CFTCSessionID									MSessionID;
		// Adresa Sender. Vyuziva sa v EndAcceptChannel() CL, pri vytvarani CH, ktory potrbuje RemoteAddress.
		private string											MSourceAddress;
		// Jedinecny identifikator suboru - 6 cislic.
		private string											MFileID;
		// Typ packetu - BEGIN, END, MESSAGE.
		private EMessageType									MMessageType;
		// Samotna M.
		private Message											MMessage;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Tento kontruktor sa vyuziva pri deserializacii, kde sa naplni cez ReadMessageWithEncoder().
		public CFTCPacket()
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MMessageType=EMessageType.E_MT_UNKNOWN;
		}
//-------------------------------------------------------------------------------------------------------
		// Tento kontruktor sa vyuziva pri serializacii, kde sa naplni cez WriteMessageWithEncoder().
		public CFTCPacket(DateTime DateTime, CFTCSessionID SessionID, string SourceAddress, string FileID, EMessageType MessageType, Message Message)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MDateTime=DateTime;
			MSessionID=SessionID;
			MSourceAddress=SourceAddress;
			MFileID=FileID;
			MMessageType=MessageType;
			MMessage=Message;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public DateTime											DateTime
		{
			get
			{
				return(MDateTime);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CFTCSessionID									SessionID
		{
			get
			{
				return(MSessionID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											SourceAddress
		{
			get
			{
				return(MSourceAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											FileID
		{
			get
			{
				return(MFileID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public EMessageType										MessageType
		{
			get
			{
				return(MMessageType);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public Message											Message
		{
			get
			{
				return(MMessage);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public MessageHeaders									MessageHeaders
		{
			get
			{
				return(MMessage.Headers);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Cita packet header - teda vsetko ostatne okrem samotnej M.
		private void ReadPacketHeader(BinaryReader BR)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MDateTime=DateTime.FromBinary(BR.ReadInt64());
			MSessionID=new CFTCSessionID(BR.ReadString());
			MSourceAddress=BR.ReadString();
			MFileID=BR.ReadString();
			MMessageType=(EMessageType) BR.ReadInt32();
		}
//-------------------------------------------------------------------------------------------------------
		// Zapisuje packet header - teda vsetko ostatne okrem samotnej M.
		private void WritePacketHeader(BinaryWriter BW)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			BW.Write(MDateTime.ToBinary());
			BW.Write(MSessionID.SessionID);
			BW.Write(MSourceAddress);
			BW.Write(MFileID);
			BW.Write((int) MMessageType);
			// Musim urobit Flush().
			BW.Flush();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Citanie packetu zo MemoryStream - ten bol vycitany zo suboru.
		// Na deserializaciu M sa pouziva MessageEncoder - ziskany z ME BE.
		public void ReadMessageWithEncoder(MemoryStream MS, MessageEncoder ME)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			try
			{
				// Obalim Stream objektom BinaryReader aby som mohol citat header.
				BinaryReader			BR=new BinaryReader(MS);

				// Nacitam header.
				ReadPacketHeader(BR);

				// Nacitam M zo Streamu.
				Message					TempMessage=ME.ReadMessage(MS,CSettings.MaxSizeOfMessageHeaders);
				// !!! Kedze M uz nie je v stave Created, nie je mozne s nou pracovat (s jej body). Preto musim vtvorit jej kopiou.
				// !!! Teda musim urobit kopiu, pretoze po uzavreti FileStream sa uzavrel aj XmlDictionaryReader a s M sa nedalo pracovat.
				// Vytovorim do buffra kopiu.
				MessageBuffer			MB=TempMessage.CreateBufferedCopy(CSettings.MaxSizeOfMessage);

				// A teraz samotnu kopiu M.
				MMessage=MB.CreateMessage();
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
		// Zapis packetu do MemoryStream - ten sa zapise do suboru.
		// Na serializaciu M sa pouziva MessageEncoder - ziskany z ME BE.
		public MemoryStream WriteMessageWithEncoder(MessageEncoder ME)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			try
			{
				// Vytvorim Stream do ktoreho zapisujem.
				MemoryStream			MS=new MemoryStream();
				// Obalim Stream objektom BinaryWriter, aby som mohol zapisat header.
				BinaryWriter			BW=new BinaryWriter(MS);

				// Zapisem header.
				WritePacketHeader(BW);

				// Zapisem M.
				ME.WriteMessage(MMessage,MS);
				// Resetnem poziciu Streamu na zaciatok.
				MS.Position=0;

				return(MS);
			}
			catch(Exception E)
			{
				CSettings.Log.Write(CDebugHelper.GetExceptionString(E),ELogRecordType.E_LRT_EXCEPTION);
				throw;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------