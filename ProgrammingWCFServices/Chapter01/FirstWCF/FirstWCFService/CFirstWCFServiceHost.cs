using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using FirstWCFLibrary;
//-------------------------------------------------------------------------------------------------------
namespace FirstWCFService
{
//-------------------------------------------------------------------------------------------------------
	internal class CFirstWCFServiceHost
	{
//-------------------------------------------------------------------------------------------------------
		private ServiceHost										MHost1;
		private ServiceHost										MHost2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal CFirstWCFServiceHost()
		{
			MHost1=new ServiceHost(typeof(CStringOperationsService));
			MHost2=new ServiceHost(typeof(CMathOperationsService));


			MHost1.OpenTimeout=new TimeSpan(0,0,10);
			MHost2.OpenTimeout=new TimeSpan(0,0,10);

			MHost1.CloseTimeout=new TimeSpan(0,0,10);
			MHost2.CloseTimeout=new TimeSpan(0,0,10);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal void Start()
		{
			try
			{
				MHost1.Open();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}

			try
			{
				MHost2.Open();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		internal void Stop()
		{
			try
			{
				if (MHost1.State==CommunicationState.Opened==true || MHost1.State==CommunicationState.Opening==true)
					MHost1.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}

			try
			{
				if (MHost2.State==CommunicationState.Opened==true || MHost2.State==CommunicationState.Opening==true)
					MHost2.Close();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------