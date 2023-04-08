using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using MyDataContractResolver;
//-------------------------------------------------------------------------------------------------------
namespace DataContractResolversService
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
				using(ServiceHost SH=new ServiceHost(typeof(CTestService)))
				{
					try
					{
						// Pridam Contract BH.
						foreach(ServiceEndpoint SE in SH.Description.Endpoints)
						{
							CMyDataContractResolver						Resolver=new CMyDataContractResolver(true,false);
							CMyDataContractResolverContractBehavior		DCRCB=new CMyDataContractResolverContractBehavior(Resolver);

							SE.Contract.Behaviors.Add(DCRCB);
						}

						SH.Open();

						Console.WriteLine("Service is OPENED !");

						Console.WriteLine("Press any key to CLOSE Service !");
						Console.ReadLine();
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
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