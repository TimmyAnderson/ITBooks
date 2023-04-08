using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalDurableServicesClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			string			ID;

			// Vytvorim WF a skoncim PROXY.
			using(CProxy Proxy=new CProxy())
			{
				Proxy.StartWorkflow("Timmy");
				ID=Proxy.GetInstanceID();
				Console.WriteLine(string.Format("ID: {0} !",ID));
			}

			Console.WriteLine("Press any key to CONTINUE !");
			Console.ReadLine();

			// Pripojim sa na ten isty WF - a zapisem VYKONAM TRANSAKCIU.
			using(CProxy Proxy=new CProxy(ID))
			{
				Proxy.DoTransaction("Jenny",true);
			}

			try
			{
				// Pripojim sa na ten isty WF - a zapisem VYKONAM NEUSPESNU TRANSAKCIU.
				using(CProxy Proxy=new CProxy(ID))
				{
					try
					{
						Proxy.DoTransaction("Atreyu",false);
					}
					catch(Exception E)
					{
						Console.WriteLine("EXCEPTION: {0} !",E.Message);
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: {0} !",E.Message);
			}

			// Pripojim sa na ten isty WF a UKONCIM HO.
			using(CProxy Proxy=new CProxy(ID))
			{
				Proxy.FinishWorkflow();
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

			try
			{
				Test();
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: {0} !",E.Message);
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------