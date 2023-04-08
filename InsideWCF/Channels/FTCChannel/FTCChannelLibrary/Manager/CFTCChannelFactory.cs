using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Text;
using System.IO;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda realizuje moj CF.
	!!! Implementuje aj rozhranie IFTCCloseSessionNotification, ALE NEPOUZIVA SA, pretoze CF base (ChannelFactoryBase<IDuplexSessionChannel>) si sam dokaze manageovat to, ktore CH su este otvorene a pri Close() ich korektne zastavit.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCChannelFactory : ChannelFactoryBase<IDuplexSessionChannel>, IFTCCloseSessionNotification
	{
//-------------------------------------------------------------------------------------------------------
		// Referencia na Transpoer BE.
		private TransportBindingElement							MBindingElement;
		// Referencia na EncoderFactory - iba sa preposiela do CH.
        private MessageEncoderFactory							MEncoderFactory;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCChannelFactory(TransportBindingElement BindingElement, BindingContext Context)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			MBindingElement=BindingElement;

			// !!! Ziskam ME BE z BindingParameters. ME BE tak sam seba ulozil.
            MessageEncodingBindingElement	EncodingBindingElement=Context.BindingParameters.Remove<MessageEncodingBindingElement>();

			// Vytvorim EncoderFactory z ME BE.
			MEncoderFactory=EncodingBindingElement.CreateMessageEncoderFactory();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Tu sa vytvara novy CH.
		protected override IDuplexSessionChannel OnCreateChannel(EndpointAddress Address, Uri Via)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim Sender address.
			string					LocalAddress=Address.Uri.AbsoluteUri;
			// Vytvorim receiver address.
			string					RemoteAddress=Address.Uri.AbsoluteUri;
			// Vytvorim nove SessionID - GUID.
			CFTCSessionID			SessionID=new CFTCSessionID();
			// Vytvorim novy CH.
			IDuplexSessionChannel	Channel=new CFTCDuplexChannel(this,SessionID,false,new Uri(LocalAddress),new Uri(RemoteAddress),MEncoderFactory.CreateSessionEncoder());

			return(Channel);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Tu sa nerobi nic.
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// !!! V base metode sa zastavia vsetky este otvorene CH. Avsak aj ked som nasledujuci riadok vyhodil tak sa CH ukoncili a CF skoncil korektne.
			base.OnClose(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			// !!! V base metode sa abortuju vsetky este otvorene CH.
			base.OnAbort();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndOpen(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void RemoveSession(CFTCSessionID SessionID)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// !!! Nemusi robit nic, kedze ChannelFactoryBase<T> SAMA ukoncuje (cez Close()) vsetky CH, ktore otvoril a sama si drzi info o tom ktore CH su este otvorene.
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------