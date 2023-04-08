using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Security;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ProtectionLevel
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
				using(ServiceHost SH1=new ServiceHost(typeof(CNonSecureContract)))
				{
					try
					{
						SH1.Open();
						Console.WriteLine(string.Format("CNonSecureContract SUCCESSFULLY OPENED !"));
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("OPENING CNonSecureContract FAILED: [{0}] !",E.Message));
					}
				}

				using(ServiceHost SH2=new ServiceHost(typeof(CSecureContract)))
				{
					try
					{
						SH2.Open();
						Console.WriteLine(string.Format("CSecureContract SUCCESSFULLY OPENED !"));
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("OPENING CSecureContract FAILED: [{0}] !",E.Message));
					}
				}

				Console.WriteLine("Press any key to STOP !");
				Console.ReadLine();
			}
			catch(Exception E)
			{
				Console.WriteLine("EXCEPTION: {0} !",E.Message);
			}

			Console.WriteLine("Press any key to EXIT");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------