using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using SecurityWithPrivateQueuesService;
//-------------------------------------------------------------------------------------------------------
namespace SecurityWithPrivateClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using (ChannelFactory<IPrintService> CF=new ChannelFactory<IPrintService>("Proxy"))
				{
					try
					{
						// !!! Moze tu byt USER ACCOUNT, ak na SERVICE je nastavena AUTHENTICATION voci WINDOWS ACCOUNT - co je DEFAULT.
						//CF.Credentials.UserName.UserName="administrator";
						//CF.Credentials.UserName.Password="************";

						// !!! Kedze pre jednoduchost som AUTHENTICATION nastavil na CUSTOM a povolil hocijaky obsah USERNAME a PASSWORD, tak tu moze byt HOCICO.
						CF.Credentials.UserName.UserName="Timmy";
						CF.Credentials.UserName.Password="Anderson";


						CF.Open();

						using (IDisposable Proxy=(IDisposable) CF.CreateChannel())
						{
							try
							{
								ICommunicationObject	CO=(ICommunicationObject) Proxy;

								CO.Open();

								IPrintService			TypedProxy=(IPrintService) Proxy;

								TypedProxy.PrintText("Timmy Anderson");
							}
							catch(Exception E)
							{
								Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
							}
						}
					}
					catch(Exception E)
					{
						Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
					}
				}
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E));
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