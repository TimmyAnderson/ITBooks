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
// Trieda implementuje funkcnost pre Request-Response - Sender.
//-------------------------------------------------------------------------------------------------------
	internal class CLCRequestChannel : CLCChannelBase, IRequestChannel
	{
//-------------------------------------------------------------------------------------------------------
		// Uklada inner CH, ale na rozdiel od CLCChannelBase uz typovany na prislusny Shape.
		protected IRequestChannel								MTypedInnerChannel;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CLCRequestChannel(ChannelManagerBase ChannelManagerBase, IRequestChannel InnerChannel, CLogData LogData)
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
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response SA VYPISUJE TIEZ.
		public IAsyncResult BeginRequest(Message Message, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Message!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " REQUEST:",Message);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(MTypedInnerChannel.BeginRequest(Message,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response SA VYPISUJE TIEZ.
		public IAsyncResult BeginRequest(Message Request, TimeSpan Timeout, AsyncCallback Callback, object State)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Request!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " REQUEST:",Request);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(MTypedInnerChannel.BeginRequest(Request,Timeout,Callback,State));
		}
//-------------------------------------------------------------------------------------------------------
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response SA VYPISUJE TIEZ.
		public Message Request(Message Request)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Request!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " Request: ",Request);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			Message			Response=MTypedInnerChannel.Request(Request);

			if (Response!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " Response: ",Response);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Response);
		}
//-------------------------------------------------------------------------------------------------------
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response SA VYPISUJE TIEZ.
		public Message Request(Message Request, TimeSpan Timeout)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			if (Request!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " Request: ",Request);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			Message			Response=MTypedInnerChannel.Request(Request,Timeout);

			if (Response!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " Response: ",Response);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Response);
		}
//-------------------------------------------------------------------------------------------------------
		// 1. Vypise M do logu.
		// 2. Preposiela volanie nizsie do CS.
		// 3. Response SA VYPISUJE TIEZ.
		public Message EndRequest(IAsyncResult Result)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			Message			Response=MTypedInnerChannel.EndRequest(Result);

			if (Response!=null)
				base.MLogData.WriteLogMessage(CDebugHelper.GetMethodCallString() + " Response: ",Response);
			else
				MLogData.WriteLog(CDebugHelper.GetMethodCallString(),"Message is null");

			return(Response);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------