using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FTCSharedLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FTCChannelLibrary
{
//-------------------------------------------------------------------------------------------------------
/*
	Trieda realizuje moj CL.
	Implementuje aj rozhranie IFTCCloseSessionNotification nato aby CH mohol CL notifikovat ked sa usmepsne ukonci, aby ho CL znova vo svojom Close() sa nepokusil ukoncit.
*/
//-------------------------------------------------------------------------------------------------------
	public class CFTCChannelListener : ChannelListenerBase<IDuplexSessionChannel>, IFTCCloseSessionNotification
	{
//-------------------------------------------------------------------------------------------------------
		// Trieda realizujuca asynchronnu operaciu AcceptChannel.
		private CChannelAcceptChannelThread						MCACT;
		// Referenica na Transport BE.
		private TransportBindingElement							MBindingElement;
		// Adresa na ktorej caka packety.
		private Uri												MAddress;
		// Adresar z ktoreho citam dosle packety - odvedeny z adresy.
		private string											MDirectory;
		// Encoder factory - z nej sa generuje MessageEncoder pouzivany pri serializacii a deserializacii M.
        private MessageEncoderFactory							MEncoderFactory;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFTCChannelListener(TransportBindingElement BindingElement, BindingContext Context)
		{
			CSettings.Log.Write(CDebugHelper.GetConstructorCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim meno adresara na ktorom cakam packety z adresy.
			MDirectory=string.Format(@"{0}/Receiver",Context.ListenUriBaseAddress.AbsolutePath);

			// !!! Adresa musi byt na strane Service aj Client UPLNE ZHODNA.
			MAddress=new Uri(Context.ListenUriBaseAddress.AbsoluteUri);
			MBindingElement=BindingElement;

			// !!! Ziskam ME BE z BindingParameters. ME BE tak sam seba ulozil.
            MessageEncodingBindingElement	EncodingBindingElement=Context.BindingParameters.Remove<MessageEncodingBindingElement>();

			// Vytvorim EncoderFactory z ME BE.
			MEncoderFactory=EncodingBindingElement.CreateMessageEncoderFactory();

			MCACT=new CChannelAcceptChannelThread(MDirectory,base.DefaultCloseTimeout,MEncoderFactory.CreateSessionEncoder());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override Uri										Uri
		{
			get
			{
				return(MAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginAcceptChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Zaciatok cakania na CH. Iba delegujem na CChannelAcceptChannelThread, kde je cela logika.
			return(MCACT.BeginAcceptChannel(Timeout,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IDuplexSessionChannel OnEndAcceptChannel(IAsyncResult Result)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Vytvorim pomcou triedu, ktora sluzi ako class factory pre moj CH.
			CFTCDuplexChannelCreator	DCC=new CFTCDuplexChannelCreator(this,true,MAddress,MEncoderFactory.CreateSessionEncoder());

			// Delegujem na CChannelAcceptChannelThread, kde je cela logika. V navratovej hodnote moze byt bud novy CH, vytvoreny pomocou CFTCDuplexChannelCreator, alebo NULL ak sa CL ukoncuje, alebo vyprsal timeout.
			IDuplexSessionChannel		CH=MCACT.EndAcceptChannel(Result,DCC);

            return(CH);
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnOpen(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Spustim thread cakajuci na prichod noveho CH.
			MCACT.Start();
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnClose(TimeSpan Timeout)
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Skoncim thread cakajuci na prichod noveho CH.
			MCACT.Stop();
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnAbort()
		{
			CSettings.Log.Write(CDebugHelper.GetMethodCallString(),ELogRecordType.E_LRT_METHOD_CALL);

			// Iba delegujem na Close().
			Close(TimeSpan.Zero);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected override IDuplexSessionChannel OnAcceptChannel(TimeSpan Timeout)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginWaitForChannel(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override bool OnEndWaitForChannel(IAsyncResult Result)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override bool OnWaitForChannel(TimeSpan Timeout)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			CSettings.Log.Write(string.Format("!!! NO IMPLEMENTATION - EXCEPTION - {0}",CDebugHelper.GetMethodCallString()),ELogRecordType.E_LRT_EXCEPTION);
			throw(new Exception("The method or operation is not implemented."));
		}
//-------------------------------------------------------------------------------------------------------
		protected override void OnEndClose(IAsyncResult Result)
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

			MCACT.RemoveSession(SessionID);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------