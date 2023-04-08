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
// Trieda implementuje funkcnost pre OneWay - Sender.
//-------------------------------------------------------------------------------------------------------
	internal class CLCOutputChannel : CLCChannelBase, IOutputChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		protected IOutputChannel								MTypedInnerChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCOutputChannel(ChannelManagerBase ChannelManagerBase, IOutputChannel InnerChannel, CLogData LogData)
			: base(ChannelManagerBase, InnerChannel, LogData)
		{
			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MTypedInnerChannel=InnerChannel;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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
// Metody, ktore nemaju ako parameter M iba preposielaju volanie do CH nizsie v CS. Tieto metody mozu byt implementovane v NTCH najme vtedy ak by napriklad som potreboval z jednej M vytovrit vdaka protokolu niekolko - napriklad WS security. Naopak v TCH maju klucovy vyznam, kedze musia realizovat synchronne, alebo asynchronne zasielanie M.
// Avsak metody, ktore maju M robia aj vypis do logu. Tieto mozu byt v NTCH vyuzite napriklad na zasielanie vicerych M (napriklad pri WS-security), alebo neajke dodatocne operacii vyplyvajuce z protokolu. Samzorejme v TCH je impelemntacia klucova.
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