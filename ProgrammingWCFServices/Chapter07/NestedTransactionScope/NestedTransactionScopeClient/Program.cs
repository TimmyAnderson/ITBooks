using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using NestedTransactionScopeHost;
//-------------------------------------------------------------------------------------------------------
namespace NestedTransactionScopeClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		private static void Test()
		{
			try
			{
				using(ChannelFactory<INestedTSService> CF=new ChannelFactory<INestedTSService>("EP"))
				{
					using(IDisposable Disp=(CF.CreateChannel() as IDisposable))
					{
						INestedTSService				Proxy=Disp as INestedTSService;

						// Nepotvrdim transakciu - vysledok je ROLLBACK.
						Proxy.DoTransaction("Jenny",false);

						// Potvrdim transakciu - vysledok je COMMIT.
						Proxy.DoTransaction("Timmy",true);
					}
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