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
// Trieda implementuje funkcnost pre Duplex - Sender a Duplex - Receiver.
//-------------------------------------------------------------------------------------------------------
	internal class CLCDuplexChannel : CLCChannelBase, IDuplexChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		protected IDuplexChannel								MTypedInnerChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCDuplexChannel(ChannelManagerBase ChannelManagerBase, IDuplexChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase, InnerChannel, LogData)
		{
			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MTypedInnerChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// RECEIVER.
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
		public EndpointAddress									RemoteAddress
		{
			get
			{
				MLogData.WriteLog(CDebugHelper.GetMethodCallString());
				return(MTypedInnerChannel.RemoteAddress);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// SENDER.
//-------------------------------------------------------------------------------------------------------
		public Uri												Via
		{
			get
			{
				MLogData.WriteLog(CDebugHelper.GetMethodCallString());
				return(MTypedInnerChannel.Via);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Receiver:
//				Metody, ktore nemaju ako parameter M iba preposielaju volanie do CH nizsie v CS. Tieto metody mozu byt implementovane v NTCH najme vtedy ak by napriklad som potreboval z jednej M vytovrit vdaka protokolu niekolko - napriklad WS security. Naopak v TCH maju klucovy vyznam, kedze musia realizovat synchronny, alebo asynchronny zber M.
//				Avsak metody, ktore maju M robia aj vypis do logu. Tieto mozu byt v NTCH vyuzite napriklad na spracovanie vicerych M, ktore boli prijate (napriklad pri WS-security), alebo neajke dodatocne operacii vyplyvajuce z protokolu. Samzorejme v TCH je impelemntacia klucova.
// Sender:
//				Metody, ktore nemaju ako parameter M iba preposielaju volanie do CH nizsie v CS. Tieto metody mozu byt implementovane v NTCH najme vtedy ak by napriklad som potreboval z jednej M vytovrit vdaka protokolu niekolko - napriklad WS security. Naopak v TCH maju klucovy vyznam, kedze musia realizovat synchronne, alebo asynchronne zasielanie M.
//				Avsak metody, ktore maju M robia aj vypis do logu. Tieto mozu byt v NTCH vyuzite napriklad na zasielanie vicerych M (napriklad pri WS-security), alebo neajke dodatocne operacii vyplyvajuce z protokolu. Samzorejme v TCH je impelemntacia klucova.
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// RECEIVER.
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginReceive(AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(this.BeginReceive(this.DefaultReceiveTimeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public Message Receive()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			Message		Ret=MTypedInnerChannel.Receive();

			if (Ret!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public Message Receive(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			Message		Ret=MTypedInnerChannel.Receive(Timeout);

			if (Ret!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public Message EndReceive(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			Message		Ret=MTypedInnerChannel.EndReceive(Result);

			if (Ret!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Ret);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginTryReceive(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginTryReceive(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public bool TryReceive(TimeSpan Timeout, out Message Message)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			bool		Ret=MTypedInnerChannel.TryReceive(Timeout, out Message);

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public bool EndTryReceive(IAsyncResult Result, out Message Message)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			bool		Ret=MTypedInnerChannel.EndTryReceive(Result, out Message);

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public IAsyncResult BeginWaitForMessage(TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.BeginWaitForMessage(Timeout, Callback, State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public bool WaitForMessage(TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.WaitForMessage(Timeout));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public bool EndWaitForMessage(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			return(MTypedInnerChannel.EndWaitForMessage(Result));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// SENDER.
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public IAsyncResult BeginSend(Message Message, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(MTypedInnerChannel.BeginSend(Message,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public IAsyncResult BeginSend(Message Message, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(MTypedInnerChannel.BeginSend(Message,Timeout,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public void Send(Message Message)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			MTypedInnerChannel.Send(Message);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		public void Send(Message Message, TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString(),Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			MTypedInnerChannel.Send(Message,Timeout);
		}
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// Iba preposiela volanie nizsie do CS.
		public void EndSend(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());
			MTypedInnerChannel.EndSend(Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------