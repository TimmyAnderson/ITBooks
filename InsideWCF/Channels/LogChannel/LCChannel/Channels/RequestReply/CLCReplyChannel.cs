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
// Trieda implementuje funkcnost pre Request-Response - Receiver.
//-------------------------------------------------------------------------------------------------------
	internal class CLCReplyChannel : CLCChannelBase, IReplyChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		protected IReplyChannel									MTypedInnerChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCReplyChannel(ChannelManagerBase ChannelManagerBase, IReplyChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase, InnerChannel, LogData)
		{
			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MTypedInnerChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public EndpointAddress									LocalAddress
		{
			get
			{
				MLogData.WriteLog(CDebugHelper.GetMethodCallString());
				return(MTypedInnerChannel.LocalAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Metody, ktore nemaju ako parameter M iba preposielaju volanie do CH nizsie v CS. Tieto metody mozu byt implementovane v NTCH najme vtedy ak by napriklad som potreboval z jednej M vytovrit vdaka protokolu niekolko - napriklad WS security. Naopak v TCH maju klucovy vyznam, kedze musia realizovat synchronny, alebo asynchronny zber M.
// Avsak metody, ktore maju M robia aj vypis do logu. Tieto mozu byt v NTCH vyuzite napriklad na spracovanie vicerych M, ktore boli prijate (napriklad pri WS-security), alebo neajke dodatocne operacii vyplyvajuce z protokolu. Samzorejme v TCH je impelemntacia klucova.
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginReceiveRequest(AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(this.BeginReceiveRequest(this.DefaultReceiveTimeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginReceiveRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginReceiveRequest(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response nie je mozne vypisat, lebo ta je zasielana cez metody RequestContext.
		public RequestContext ReceiveRequest()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			RequestContext	Ret=MTypedInnerChannel.ReceiveRequest();

			if (Ret!=null && Ret.RequestMessage!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret.RequestMessage);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response nie je mozne vypisat, lebo ta je zasielana cez metody RequestContext.
		public RequestContext ReceiveRequest(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			RequestContext	Ret=MTypedInnerChannel.ReceiveRequest(Timeout);

			if (Ret!=null && Ret.RequestMessage!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret.RequestMessage);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response nie je mozne vypisat, lebo ta je zasielana cez metody RequestContext.
		public RequestContext EndReceiveRequest(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			RequestContext	Ret=MTypedInnerChannel.EndReceiveRequest(Result);

			if (Ret!=null && Ret.RequestMessage!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret.RequestMessage);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginTryReceiveRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginTryReceiveRequest(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response nie je mozne vypisat, lebo ta je zasielana cez metody RequestContext.
		public bool TryReceiveRequest(TimeSpan Timeout, out RequestContext RequestContext)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			bool		Ret=MTypedInnerChannel.TryReceiveRequest(Timeout, out RequestContext);

			if (RequestContext!=null && RequestContext.RequestMessage!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),RequestContext.RequestMessage);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response nie je mozne vypisat, lebo ta je zasielana cez metody RequestContext.
		public bool EndTryReceiveRequest(IAsyncResult Result, out RequestContext RequestContext)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			bool		Ret=MTypedInnerChannel.EndTryReceiveRequest(Result, out RequestContext);

			if (RequestContext!=null && RequestContext.RequestMessage!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),RequestContext.RequestMessage);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginWaitForRequest(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginWaitForRequest(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public bool WaitForRequest(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.WaitForRequest(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public bool EndWaitForRequest(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.EndWaitForRequest(Result));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------