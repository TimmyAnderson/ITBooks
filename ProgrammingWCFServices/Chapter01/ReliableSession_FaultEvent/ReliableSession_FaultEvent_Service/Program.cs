using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ReliableSession_FaultEvent_Shared;
//-----------------------------------------------------------------------------------------------------------
namespace ReliableSession_FaultEvent_Service
{
//-----------------------------------------------------------------------------------------------------------
	class Program
	{
//-----------------------------------------------------------------------------------------------------------
		private static void SH_Faulted(object Sender, EventArgs E)
		{
			Console.WriteLine("!!!!! HOST received FAULTED STATE !!!!!");
		}
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CSimpleTestInterface)))
				{
					SH.Faulted+=new EventHandler(SH_Faulted);

					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
					
					SH.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("!!!!! EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-----------------------------------------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------------------------------------