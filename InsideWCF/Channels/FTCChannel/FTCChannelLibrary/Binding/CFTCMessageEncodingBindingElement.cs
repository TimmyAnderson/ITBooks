using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace FTCSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda implementujuca moj ME BE.
	!!! Tento BE nevytvara CH, ale iba prenesie SAM SEBA cez kolekciu BindingParameters do Transport BE a ten zas ju posle cez CL a CF az do CH.
*/
//-------------------------------------------------------------------------------------------------------
    public class CFTCMessageEncodingBindingElement : MessageEncodingBindingElement
    {
//-------------------------------------------------------------------------------------------------------
		// Verzia SOAP, ktora sa bude pozivat pri serializacii a deserializacii M.
        private MessageVersion									MVersion;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public CFTCMessageEncodingBindingElement(MessageVersion Version)
        {
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MVersion=Version;
        }
//-------------------------------------------------------------------------------------------------------
        public CFTCMessageEncodingBindingElement(CFTCMessageEncodingBindingElement Other)
        {
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

            MVersion=Other.MVersion;
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
        public override MessageVersion							MessageVersion
        {
            get
            {
                return(MVersion);
            }
            set
            {
                MVersion=value;
            }
        }
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// !!! Klucova metoda ME BE. Jej ulohou je vytvorit class factory k MessageEncoder.
        public override MessageEncoderFactory CreateMessageEncoderFactory()
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim CFTCMessageEncoderFactory a tak zas vytvora CFTCMessageEncoder, kde sa realizuje samotna serializacia a deserializacia Message. 
            return(new CFTCMessageEncoderFactory(this));
        }
//-------------------------------------------------------------------------------------------------------
        public override BindingElement Clone()
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Klon vytvorim tak, ze vytvorim novu instanciu a pouzijem jej copy-constructor.
            return(new CFTCMessageEncodingBindingElement(this));
        }
//-------------------------------------------------------------------------------------------------------
        public override bool CanBuildChannelFactory<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Akceptujem iba Duplex Session CH.
            if (typeof(TChannel)!=typeof(IDuplexSessionChannel))
                return(false);

			// !!! Pridam sam seba do BindingParameters aby ma odtialto mohol Tranport BE vytiahnut a poslat skrze CF do CH, kde sa pouzije na seriazliaciu a deserializaciu Message.
            Context.BindingParameters.Add(this);

			// Poslem vnutornemu BE (u mna CFTCTransportBindingElement) na spracovanie.
            return(Context.CanBuildInnerChannelFactory<TChannel>());
        }
//-------------------------------------------------------------------------------------------------------
        public override bool CanBuildChannelListener<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Akceptujem iba Duplex Session CH.
            if (typeof(TChannel)!=typeof(IDuplexSessionChannel))
                return(false);

			// !!! Pridam sam seba do BindingParameters aby ma odtialto mohol Tranport BE vytiahnut a poslat skrze CL do CH, kde sa pouzije na seriazliaciu a deserializaciu Message.
            Context.BindingParameters.Add(this);

			// Poslem vnutornemu BE (u mna CFTCTransportBindingElement) na spracovanie.
            return(Context.CanBuildInnerChannelListener<TChannel>());
        }
//-------------------------------------------------------------------------------------------------------
        public override IChannelFactory<TChannel> BuildChannelFactory<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// !!! Pridam sam seba do BindingParameters aby ma odtialto mohol Tranport BE vytiahnut a poslat skrze CF do CH, kde sa pouzije na seriazliaciu a deserializaciu Message.
            Context.BindingParameters.Add(this);

			// Poslem vnutornemu BE (u mna CFTCTransportBindingElement) na spracovanie.
            return(Context.BuildInnerChannelFactory<TChannel>());
        }
//-------------------------------------------------------------------------------------------------------
        public override IChannelListener<TChannel> BuildChannelListener<TChannel>(BindingContext Context)
        {
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// !!! Pridam sam seba do BindingParameters aby ma odtialto mohol Tranport BE vytiahnut a poslat skrze CL do CH, kde sa pouzije na seriazliaciu a deserializaciu Message.
            Context.BindingParameters.Add(this);

			// Poslem vnutornemu BE (u mna CFTCTransportBindingElement) na spracovanie.
            return(Context.BuildInnerChannelListener<TChannel>());
        }
//-------------------------------------------------------------------------------------------------------
    }
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------