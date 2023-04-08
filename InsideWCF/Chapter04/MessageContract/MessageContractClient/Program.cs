using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using MessageContractLibrary;
//-------------------------------------------------------------------------------------------------------
namespace MessageContractClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Test()
		{
			CMessageContractProxy				Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			WSHttpBinding						WSBinding=new WSHttpBinding(SecurityMode.None);

			// Nastavim textovy encoder.
			WSBinding.MessageEncoding=WSMessageEncoding.Text;

			try
			{
				Client=new CMessageContractProxy(WSBinding,"http://localhost:4000/IMessageContractContract");

				// Otvaram kanal.
				Client.Open();

				CMyDataContract					MyDataContract1=new CMyDataContract(100,"abc");

				Client.SomeDCOperation(MyDataContract1);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				CMyDataContract					MyDataContract2=new CMyDataContract(200,"xyz");
				CMyMessageContract				MyMessageContract=new CMyMessageContract(300,MyDataContract2);

				Client.SomeMCOperation(MyMessageContract);

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(CDebugHelper.GetExceptionString(E,"FATAL EXCEPTION"));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					try
					{
						Client.Close();
						Console.WriteLine(String.Format("Close() OK"));
					}
					catch(Exception E)
					{
						Console.WriteLine(String.Format("Close() FAILED: {0} !",E.Message));
					}

					Client=null;
				}
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