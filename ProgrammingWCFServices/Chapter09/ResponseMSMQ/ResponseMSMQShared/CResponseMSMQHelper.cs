using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ResponseMSMQShared
{
//-------------------------------------------------------------------------------------------------------
	public static class CResponseMSMQHelper
	{
//-------------------------------------------------------------------------------------------------------
		public static CMyResponseContext GetMyResponseContext()
		{
			CMyResponseContext						MyResponseContext=OperationContext.Current.IncomingMessageHeaders.GetHeader<CMyResponseContext>("CMyResponseContext","ResponseMSMQShared");
			
			return(MyResponseContext);
		}
//-------------------------------------------------------------------------------------------------------
		public static void SetMyResponseContext(CMyResponseContext MyResponseContext)
		{
			MessageHeader<CMyResponseContext>		MSGHeader=new MessageHeader<CMyResponseContext>(MyResponseContext);

			OperationContext.Current.OutgoingMessageHeaders.Add(MSGHeader.GetUntypedHeader("CMyResponseContext","ResponseMSMQShared"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------