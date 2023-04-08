﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace DefaultBehaviors
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				using (ServiceHost SH=new ServiceHost(typeof(CToUpperService)))
				{
					SH.Open();

					Console.WriteLine("Press any key to STOP !");
					Console.ReadLine();
					
					SH.Close();
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