using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
//-------------------------------------------------------------------------------------------------------
namespace ResponseCalculatorService
{
//-------------------------------------------------------------------------------------------------------
	public class CServiceHostWrapper<T> : IServiceHostWrapper
	{
//-------------------------------------------------------------------------------------------------------
		private object											MSyn;
		private ServiceHost										MHost;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CServiceHostWrapper()
		{
			MSyn=new object();
			MHost=new ServiceHost(typeof(T));

			MHost.OpenTimeout=new TimeSpan(0,0,10);
			MHost.CloseTimeout=new TimeSpan(0,0,10);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public ServiceHost										Host
		{
			get
			{
				return(MHost);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void StartService()
		{
			lock(MSyn)
			{
				try
				{
					MHost.Open();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("CServiceHostWrapper.StartService() - Exception: {0} !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void StopService()
		{
			lock(MSyn)
			{
				try
				{
					if (MHost.State==CommunicationState.Opened==true || MHost.State==CommunicationState.Opening==true)
						MHost.Close();
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("CServiceHostWrapper.StopService() - Exception: {0} !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void AddServiceEndpoint<TL>(Binding EndpointBinding, string Address)
		{
			lock(MSyn)
			{
				try
				{
					MHost.AddServiceEndpoint(typeof(TL),EndpointBinding,Address);
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("CServiceHostWrapper.AddServiceEndpoint() - Exception: {0} !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void AddTCPMEXEndpoint(string MEXEndpoindName)
		{
			lock(MSyn)
			{
				try
				{
					BindingElement			BE=new TcpTransportBindingElement();
					CustomBinding			CB=new CustomBinding(BE);
					ServiceMetadataBehavior SMB;

					if ((SMB=Host.Description.Behaviors.Find<ServiceMetadataBehavior>())==null)
					{
						SMB=new ServiceMetadataBehavior();
						Host.Description.Behaviors.Add(SMB);
					}

					MHost.AddServiceEndpoint(typeof(IMetadataExchange),CB,MEXEndpoindName);
				}
				catch(Exception E)
				{
					Console.WriteLine(String.Format("CServiceHostWrapper.AddServiceEndpoint() - Exception: {0} !",E.Message));
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------