using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using ChannelFactoryService;
//-------------------------------------------------------------------------------------------------------
namespace ChannelFactoryClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				// Vytvorim ChannelFactory<>.
				ChannelFactory<IToUpperService>		CF=new ChannelFactory<IToUpperService>(new WSHttpBinding(),"http://localhost:8001/ToUpperService");

				// Vytvorim PROXY.
				IToUpperService						Proxy=CF.CreateChannel();

				// Konvertujem PROXY na ICommunicationObject.
				ICommunicationObject				CO=Proxy as ICommunicationObject;
				IDisposable							D=Proxy as IDisposable;

				using(D)
				{
					CO.Open();

					string				Ret=Proxy.ToUpper("Timmy");

					Console.WriteLine(string.Format("Value: [{0}] !",Ret));

					// Nie je potrebny, lebo sa bude volat Dispose().
					CO.Close();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			Test();

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------