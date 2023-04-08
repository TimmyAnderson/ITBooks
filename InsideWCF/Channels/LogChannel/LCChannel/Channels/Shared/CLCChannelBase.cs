using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
using Log;
//-------------------------------------------------------------------------------------------------------
namespace LCChannel
{
//-------------------------------------------------------------------------------------------------------
// Trieda reprezentuje base triedu pre vsetky CH.
// Jej hlavnou ulohou je poskytnut base implementujuci state machine, ci IChannel.
// !!! Je generic kedze sluzi pre vsetky Shapes. Tento parameter bude vlastne rozhranim CH ako napriklad IOutputChannel pre OneWay Sender, ci IReplyChannel pre Request&Response MEP.
//-------------------------------------------------------------------------------------------------------
	internal class CLCChannelBase : ChannelBase
	{
//-------------------------------------------------------------------------------------------------------
		// Obsahuje referenciu na CH nizsie v CS. Tato referencia neobshuje Shape. Az potomkovia ju maju.
		protected IChannel										MInnerChannel;
		// Data pre log. Sluzi aj ako property CH ku ktorej sa pristupuje cez GetProperty<>().
		protected CLogData										MLogData;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Protected konstruktor. Vola ChannelBase a predava mu referenciu na ChannelManagerBase. To sa vyuziva napriklad pre notifikaciu CM pri Close CH.
		protected CLCChannelBase(ChannelManagerBase ChannelManagerBase, IChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase)
		{
			MLogData=LogData;

			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			// Inner CH nesmie byt null - teda tento CH nesmie byt na bottom CS - teda nie je to transport CH.
			if (InnerChannel==null)
				throw(new ArgumentException("InnerChannel must not be null"));

			MInnerChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Abstraktne metody.
// ??? Musia volat metody CH nizsie v CS a to preto, lebo WCF CH rozhrania ci triedy NEMAJU ANI PARU O CS. Ten poznam iba moj CH a preto musim v tychto metodach, ktore implementuju samotnu funkcnost CH volat CH nizsie v CS.
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		protected override void OnAbort()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			MInnerChannel.Abort();
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.BeginClose().
		protected override IAsyncResult OnBeginClose(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam BeginClose() nie OnBeginClose() kedze to nie je sucastou ICommunicationObject.
			return(MInnerChannel.BeginClose(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.BeginOpen().
		protected override IAsyncResult OnBeginOpen(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam BeginOpen() nie OnBeginOpen() kedze to nie je sucastou ICommunicationObject.
			return(MInnerChannel.BeginOpen(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.Close().
		protected override void OnClose(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam Close() nie OnClose() kedze to nie je sucastou ICommunicationObject.
			MInnerChannel.Close(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.EndClose().
		protected override void OnEndClose(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam EndClose() nie OnEndClose() kedze to nie je sucastou ICommunicationObject.
			MInnerChannel.EndClose(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.EndOpen().
		protected override void OnEndOpen(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam EndOpen() nie OnEndOpen() kedze to nie je sucastou ICommunicationObject.
			MInnerChannel.EndOpen(Result);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Vyvola ju ChannelBase.Open().
		protected override void OnOpen(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			// Volam Open() nie OnOpen() kedze to nie je sucastou ICommunicationObject.
			MInnerChannel.Open(Timeout);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Virtualne metody.
// Musia volat vzdy metodu, ktoru dedia.
// ??? Nemusia vsak volat moedy CS nizsie v stacku, kedze sa jedna iba o notifikacne metody. Volanie CH nizsie v stacku ma na starosti implementacia abstraktnych metod.
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		// Metoda vracia property CH.
		// Ja som implementoval property tyypu CLogData. Ostatne su zaslane do CH nizsie v CS.
		public override T GetProperty<T>()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (typeof(T)==typeof(CLogData))
				return((T) ((object) MLogData));
			else
				return(MInnerChannel.GetProperty<T>());
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		protected override void OnClosed()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			base.OnClosed();
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		protected override void OnClosing()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			base.OnClosing();
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		protected override void OnFaulted()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			base.OnFaulted();
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		protected override void OnOpened()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			base.OnOpened();
		}
//-------------------------------------------------------------------------------------------------------
		// Virtualna metoda.
		protected override void OnOpening()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			base.OnOpening();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------