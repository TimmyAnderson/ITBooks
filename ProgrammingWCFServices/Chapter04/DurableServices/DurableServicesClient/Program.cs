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
namespace DurableServicesClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test1()
		{
			string			ID;

			// Vytvorim WF a skoncim PROXY.
			using(CProxy Proxy=new CProxy())
			{
				Proxy.SetFirstName("Timmy");
				ID=Proxy.GetInstanceID();
				Console.WriteLine(string.Format("ID: {0} !",ID));
			}

			Console.WriteLine("WF CREATED - you can now check SQL DB for new Record !");
			Console.WriteLine("Press any key to CONTINUE !");
			Console.ReadLine();

			// Pripojim sa na ten isty WF.
			using(CProxy Proxy=new CProxy(ID))
			{
				Proxy.SetLastName("Anderson");

				// Kedze totu operaciou sa ukoncuje WF - MUSIM UKONCIT AJ PROXY - stava sa NEPLATNE.
				Proxy.PrintFullNameAndFinishWFByAttribute();
			}
		}
//-------------------------------------------------------------------------------------------------------
		private static void Test2()
		{
			string			ID;

			// Vytvorim WF a skoncim PROXY.
			using(CProxy Proxy=new CProxy())
			{
				Proxy.SetFirstName("Timmy");
				ID=Proxy.GetInstanceID();
				Console.WriteLine(string.Format("ID: {0} !",ID));
			}

			Console.WriteLine("WF CREATED - you can now check SQL DB for new Record !");
			Console.WriteLine("Press any key to CONTINUE !");
			Console.ReadLine();

			// Pripojim sa na ten isty WF.
			using(CProxy Proxy=new CProxy(ID))
			{
				Proxy.SetLastName("Anderson");

				// Kedze totu operaciou sa ukoncuje WF - MUSIM UKONCIT AJ PROXY - stava sa NEPLATNE.
				Proxy.PrintFullNameAndFinishWFByCode();
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
				//Test1();
				Test2();
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