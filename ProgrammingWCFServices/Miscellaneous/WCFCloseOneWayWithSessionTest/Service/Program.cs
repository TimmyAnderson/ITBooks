﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.Threading;
using WCFCloseOneWayWithSessionTest;
//-------------------------------------------------------------------------------------------------------
namespace Service
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="SERVICE";

			try
			{
				using(ServiceHost SH=new ServiceHost(typeof(CTestService)))
				{
					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------