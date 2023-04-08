using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using FormServiceLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace FormServiceClient
{
//--------------------------------------------------------------------------------------------------------------------------------
	class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CFormServiceProxy					Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim reliability na session.
			TCPBinding.ReliableSession.Enabled=true;

			try
			{
				Client=new CFormServiceProxy(TCPBinding,"net.tcp://localhost:9001/IFormServiceContract");

				// Otvorim kanal aby som zamedzil synchornnemu volanou v dosledku toho, ze kanal este nebol otvoreny.
				Client.Open();

				Client.IncrementLabel();
				Thread.Sleep(2000);
				Client.IncrementLabel();
				Thread.Sleep(2000);
				Client.IncrementLabel();
				Thread.Sleep(2000);
				Client.DecrementLabel();
				Thread.Sleep(2000);
				Client.DecrementLabel();
				Thread.Sleep(2000);
				Client.DecrementLabel();

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();

				Console.WriteLine("ALL OK !\n");
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Console.WriteLine("BEFORE CLOSE !");
					Client.Close();
					Console.WriteLine("AFTER CLOSE !");
					Client=null;
				}
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------