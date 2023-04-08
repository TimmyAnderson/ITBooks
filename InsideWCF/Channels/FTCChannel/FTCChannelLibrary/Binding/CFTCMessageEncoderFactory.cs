using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda sluzi ako class factory pre EncoderFactory (CFTCMessageEncoder).
	!!! Je potrebne pre implementaciu ME BE a vyuziva sa pri seralizacii a deserializacii M.
*/
//-------------------------------------------------------------------------------------------------------
    public class CFTCMessageEncoderFactory : MessageEncoderFactory
    {
//-------------------------------------------------------------------------------------------------------
		// Moj MessageEncoder. Pomocna premenna do ktorej sa ulozi jej singleton instancia.
        private CFTCMessageEncoder								MEncoder=null;
		// Verzia SOAP pouzita pri serilizacii a deserializacii M.
        private MessageVersion									MVersion=null;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CFTCMessageEncoderFactory(CFTCMessageEncodingBindingElement BindingElement)
        {
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

            MVersion=BindingElement.MessageVersion;
        }
//-------------------------------------------------------------------------------------------------------
        public override MessageEncoder							Encoder
        {
            get 
            {
				// Tu sa vytvara instanciu mojej CFTCMessageEncoder. Ulozu sa do pomocnej premmenej aby bola znovupouzitelna bez nutnosti vytvarat novu instaniu.
                if (MEncoder==null)
                    MEncoder=new CFTCMessageEncoder(MVersion,CSettings.SOAPEncoder);

                return(MEncoder);
            }
        }
//-------------------------------------------------------------------------------------------------------
        public override MessageVersion							MessageVersion
        {
            get 
            {
                return(MVersion);
            }
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------