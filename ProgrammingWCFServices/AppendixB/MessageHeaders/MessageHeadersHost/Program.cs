﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace MessageHeadersHost
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="HOST";

			try
			{
				using(ServiceHost SH1=new ServiceHost(typeof(CService1)))
				{
					using(ServiceHost SH2=new ServiceHost(typeof(CService2)))
					{
						try
						{
							SH1.Open();
							SH2.Open();

							Console.WriteLine("Press any key to STOP !");
							Console.ReadLine();
						}
						catch(Exception E)
						{
							Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
						}
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------