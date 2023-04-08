using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel.Channels;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DelegatorChannel
{
//-------------------------------------------------------------------------------------------------------
	public class CDelegatorBinding : Binding
	{
//-------------------------------------------------------------------------------------------------------
		private string											MScheme;
		private BindingElementCollection						MElements;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDelegatorBinding(EBindingMode Mode)
			: this(Mode, 0, null)
		{
		}
//-------------------------------------------------------------------------------------------------------
		public CDelegatorBinding(EBindingMode BindingMode, int ElementPosition, Uri ClientBaseAddress)
		{
			if ((ClientBaseAddress==null) && (BindingMode==EBindingMode.WSDualHttp))
				throw(new ArgumentNullException("ClientBaseAddress cannot be null with WsDual Binding Mode !", "clientBaseAddress"));
	        
			switch(BindingMode)
			{
				case (EBindingMode.BasicHttp):
				{
					BasicHttpBinding		HttpBinding=new BasicHttpBinding(BasicHttpSecurityMode.None);

					MElements=HttpBinding.CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.Tcp):
				{
					MElements=new NetTcpBinding(SecurityMode.None, false).CreateBindingElements();
					MScheme="net.tcp";
				}
				break;

				case (EBindingMode.TcpRM):
				{
					MElements=new NetTcpBinding(SecurityMode.None, true).CreateBindingElements();
					MScheme="net.tcp";
				}
				break;

				case (EBindingMode.WSHttp):
				{
					MElements=new WSHttpBinding(SecurityMode.None, false).CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.WSHttpRM):
				{
					MElements=new WSHttpBinding(SecurityMode.None, true).CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.WSDualHttp):
				{
					WSDualHttpBinding		WSBinding=new WSDualHttpBinding(WSDualHttpSecurityMode.None);

					WSBinding.ClientBaseAddress=ClientBaseAddress;
					MElements=WSBinding.CreateBindingElements();
					MScheme="http";
				}
				break;

				case (EBindingMode.MSMQ):
				{
					NetMsmqBinding			MsmqBinding=new NetMsmqBinding(NetMsmqSecurityMode.None);

					MsmqBinding.ExactlyOnce=false;
					MElements=MsmqBinding.CreateBindingElements();
					MScheme="net.msmq";
				}
				break;

				case (EBindingMode.MSMQSession):
				{
					NetMsmqBinding			MsmqTransactionalBinding=new NetMsmqBinding(NetMsmqSecurityMode.None);

					MsmqTransactionalBinding.ExactlyOnce=true;
					MElements=MsmqTransactionalBinding.CreateBindingElements();
					MElements[0]=new TextMessageEncodingBindingElement(MessageVersion.Default, Encoding.UTF8);
					MScheme="net.msmq";
				}
				break;

				default:
					throw(new ArgumentOutOfRangeException("bindingMode"));
			}

			// Add the DelegatorBindingElement.
			MElements.Insert(ElementPosition, new CDelegatorBindingElement());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string									Scheme
		{
			get
			{
				return(MScheme);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override BindingElementCollection CreateBindingElements()
		{ 
			return(MElements);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------