using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
using StreamingLibrary;
//-------------------------------------------------------------------------------------------------------
namespace StreamingClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CStreamingProxy						Client=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			NetTcpBinding						TCPBinding=new NetTcpBinding();

			// Nastavim transfer mod na Streamed.
			TCPBinding.TransferMode=TransferMode.Streamed;

			// Nastavim maximalnu dlzku message.
			TCPBinding.MaxReceivedMessageSize=10*1024*1024;

			try
			{
				Client=new CStreamingProxy(TCPBinding,"net.tcp://localhost:9001/IStreamingContract");

				// !!! Tento Stream nesmiem zavriet. Urobi to WCF.
				Stream						SOut=new CMyStream();

				// Naplnim Stream.
				CStreamHelper.FillStream(SOut);

				// Presuniem Stream na zaciatok.
				SOut.Seek(0,SeekOrigin.Begin);

				// Odoslem stream do servera.
				Client.SendStream(SOut);

				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();
				Console.Clear();

				// Tu uz mozem zavriet stream.
				SOut.Close();
				SOut=null;


				Stream						SIn;

				// Odoslem stream do servera.
				SIn=Client.ReceiveStream();

				// !!! Zacnem citat Stream - METODA HO UKONCI.
				CStreamHelper.ReadStream(SIn);

				// Tu uz mozem zavriet stream.
				SIn.Close();
				SIn=null;

				Console.WriteLine("ALL OK !\n");
				Console.WriteLine("Press any key to continue !");
				Console.ReadLine();
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
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------