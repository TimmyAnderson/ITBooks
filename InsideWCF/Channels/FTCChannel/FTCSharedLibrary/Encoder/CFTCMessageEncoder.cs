using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Runtime.Serialization;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda, ktore ralizuje serializaciu a deserializaciu Message.
	Je vytvorena cez class factory CFTCMessageEncoderFactory a ta zas cez moj ME BE - CFTCMessageEncodingBindingElement.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCMessageEncoder : MessageEncoder
	{
//-------------------------------------------------------------------------------------------------------
		// Verzia SOAP pouzita pri serializacii\deserializacii M.
		private MessageVersion									MMessageVersion;
		// !!! To je moje vlastne nastavenie, ktore urcuje ako sa budu M serializaovat\deserializovat.
		// Urcuje ako Encoding sa bude pouzivat - Text, alebo Binary.
		// Ked som mal ako Body retazec 'Timmy' tak pri Text bola dlzka 573 a Binary 405 bytov.
		private ESOAPEncoder									MSOAPEncoder;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCMessageEncoder(MessageVersion MessageVersion, ESOAPEncoder SOAPEncoder)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MMessageVersion=MessageVersion;
			MSOAPEncoder=SOAPEncoder;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override MessageVersion							MessageVersion
		{
			get
			{
				CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);
				return(MMessageVersion);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string									ContentType
		{
			get
			{
				CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0} !",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public override string									MediaType
		{
			get
			{
				CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0} !",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
				throw(new Exception("The method or operation is not implemented."));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Robi deserializaciu, teda konverziu zo Stream do Message.
		public override Message ReadMessage(Stream Stream, int MaxSizeOfHeaders, string ContentType)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			XmlDictionaryReader		XDR=null;

			switch(MSOAPEncoder)
			{
				// Vytvorim Text Reader.
				case ESOAPEncoder.E_SE_TEXT:
					XDR=XmlDictionaryReader.CreateTextReader(Stream,new XmlDictionaryReaderQuotas());
				break;

				// Vytvorim Binary Reader.
				case ESOAPEncoder.E_SE_BINARY:
					XDR=XmlDictionaryReader.CreateBinaryReader(Stream,new XmlDictionaryReaderQuotas());
				break;

				default:
					throw(new InvalidOperationException("CSettings.SOAPEncoder has invalid value !"));
			}

			// Deseriazliujem data a vytvorim objekt typu Message.
			Message					Out=Message.CreateMessage(XDR,MaxSizeOfHeaders,MMessageVersion);

			return(Out);
		}
//-------------------------------------------------------------------------------------------------------
		public override void WriteMessage(Message Message, Stream Stream)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			XmlDictionaryWriter		XDW=null;

			switch(MSOAPEncoder)
			{
				// Vytvorim Text Writer.
				case ESOAPEncoder.E_SE_TEXT:
					XDW=XmlDictionaryWriter.CreateTextWriter(Stream);
				break;

				// Vytvorim Text Writer.
				case ESOAPEncoder.E_SE_BINARY:
					XDW=XmlDictionaryWriter.CreateBinaryWriter(Stream);
				break;

				default:
					throw(new InvalidOperationException("Encoder has invalid value !"));
			}

			// Seriazliujem Message.
			Message.WriteMessage(XDW);
			// !!! Musi tu byt Flush() aby sa data preniesli z buffera Stream do samotneho Streamu.
			XDW.Flush();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Nevyuzivam - neimplementovane.
		public override Message ReadMessage(ArraySegment<byte> Buffer, BufferManager BufferManager, string ContentType)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0} !",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		// Nevyuzivam - neimplementovane.
		public override ArraySegment<byte> WriteMessage(Message Message, int MaxMessageSize, BufferManager BufferManager, int MessageOffset)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0} !",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------