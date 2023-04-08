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
// Trieda implementuje moj vlastny B.
// !!! Nemusel by som vytvarat vlastny B, ale pouzit triedu CustomBinding a do jeho konstruktora dat kolekciu BE a aj mojim BE. Takto by som ziskal rovnaku funkcionalitu ako pri vytvoreni vlastneho B. Ale riesenie s vytvorenim vlastnej triedy B je elegantnejsie a more reusable.
//-------------------------------------------------------------------------------------------------------
	public class CLCBinding : Binding
	{
//-------------------------------------------------------------------------------------------------------
		private string											MScheme;
		// Data pre log.
		private CLogData										MLogData;
		private EBindingMode									MBindingMode; 
		private int												MElementPosition;
		private Uri												MClientBaseAddress;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLCBinding(CLogData LogData, EBindingMode BindingMode, int ElementPosition, Uri ClientBaseAddress)
		{
			MLogData=LogData;

			MLogData.WriteLog(CDebugHelper.GetConstructorCallString());

			MBindingMode=BindingMode;
			MElementPosition=ElementPosition;
			MClientBaseAddress=ClientBaseAddress;

			base.OpenTimeout=TimeSpan.FromMinutes(5);
			base.CloseTimeout=TimeSpan.FromMinutes(5);
			base.ReceiveTimeout=TimeSpan.FromMinutes(5);
			base.SendTimeout=TimeSpan.FromMinutes(5);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string			Scheme
		{
			get
			{
				return(MScheme);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Vytvori BE kolekciu.
		// Moj Log CH umiestni na poziciu v kolekcii zodpovedajucu parametru ElementPosition.
		private BindingElementCollection CreateBECollection(EBindingMode BindingMode, int ElementPosition, Uri ClientBaseAddress)
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			BindingElementCollection	Elements;

			if ((ClientBaseAddress==null) && (BindingMode==EBindingMode.WSDualHttp))
				throw(new ArgumentNullException("ClientBaseAddress cannot be null with WsDual Binding Mode !", "ClientBaseAddress"));
	        
			switch(BindingMode)
			{
				case (EBindingMode.BasicHttp):
				{
					BasicHttpBinding		HttpBinding=new BasicHttpBinding(BasicHttpSecurityMode.None);

					Elements=HttpBinding.CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.Tcp):
				{
					Elements=new NetTcpBinding(SecurityMode.None, false).CreateBindingElements();
					MScheme="net.tcp";
				}
				break;

				case (EBindingMode.TcpRM):
				{
					Elements=new NetTcpBinding(SecurityMode.None, true).CreateBindingElements();
					MScheme="net.tcp";
				}
				break;

				case (EBindingMode.TcpRMSec):
				{
					Elements=new NetTcpBinding(SecurityMode.Transport, true).CreateBindingElements();
					MScheme="net.tcp";
				}
				break;

				case (EBindingMode.WSHttp):
				{
					Elements=new WSHttpBinding(SecurityMode.None, false).CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.WSHttpRM):
				{
					Elements=new WSHttpBinding(SecurityMode.None, true).CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.WSDualHttp):
				{
					WSDualHttpBinding		WSBinding=new WSDualHttpBinding(WSDualHttpSecurityMode.None);

					WSBinding.ClientBaseAddress=ClientBaseAddress;
					Elements=WSBinding.CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.MSMQ):
				{
					NetMsmqBinding			MsmqBinding=new NetMsmqBinding(NetMsmqSecurityMode.None);

					MsmqBinding.ExactlyOnce=false;
					Elements=MsmqBinding.CreateBindingElements();
					MScheme="net.msmq";
				}
				break;

				case (EBindingMode.MSMQSession):
				{
					NetMsmqBinding			MsmqTransactionalBinding=new NetMsmqBinding(NetMsmqSecurityMode.None);

					MsmqTransactionalBinding.ExactlyOnce=true;
					Elements=MsmqTransactionalBinding.CreateBindingElements();
					Elements[0]=new TextMessageEncodingBindingElement(MessageVersion.Default, Encoding.UTF8);
					MScheme="net.msmq";
				}
				break;

				default:
					throw(new ArgumentOutOfRangeException("BindingMode"));
			}

			if (ElementPosition>=0)
				// Pridam svoj vlastny BE do kolekcie BE na poziciu ElementPosition.
				Elements.Insert(ElementPosition, new CLCBindingElement(MLogData));

			return(Elements);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Abstraktna metoda.
		// !!! Klucova metoda celeho BE, ktora je zodpovedna za vytvorenie SORTOVANEJ kolekcie BE.
		public override BindingElementCollection CreateBindingElements()
		{
			MLogData.WriteLog(CDebugHelper.GetMethodCallString());

			return(CreateBECollection(MBindingMode,MElementPosition,MClientBaseAddress));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------