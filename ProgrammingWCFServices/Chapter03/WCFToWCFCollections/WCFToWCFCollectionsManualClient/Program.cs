using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using WCFToWCFCollectionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsManualClient
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

			CWCFToWCFCollectionsProxy			Client=null;
			List<CName>							CollectionIn1=CCollectionHelper.GetCollection1();
			Dictionary<int,CName>				CollectionIn2=CCollectionHelper.GetCollection2();
			CMyCollection<CName>				CollectionIn3=CCollectionHelper.GetCollection3();
			List<CName>							CollectionOut1=null;
			Dictionary<int,CName>				CollectionOut2=null;
			CMyCollection<CName>				CollectionOut3=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CWCFToWCFCollectionsProxy(TCPBinding,"net.tcp://localhost:9001/IWCFToWCFCollectionsContract");

				CollectionOut1=Client.GetCollection1();
				Console.WriteLine(String.Format("Server returned GetCollection1():\n{0}",CCollectionHelper.Collection1ToString(CollectionOut1)));

				CollectionOut2=Client.GetCollection2();
				Console.WriteLine(String.Format("Server returned GetCollection2():\n{0}",CCollectionHelper.Collection2ToString(CollectionOut2)));

				CollectionOut3=Client.GetCollection3();
				Console.WriteLine(String.Format("Server returned GetCollection3():\n{0}",CCollectionHelper.Collection3ToString(CollectionOut3)));

				Client.SendCollection1(CollectionIn1);
				Console.WriteLine(String.Format("Client send SendCollection1:\n{0}",CCollectionHelper.Collection1ToString(CollectionIn1)));

				Client.SendCollection2(CollectionIn2);
				Console.WriteLine(String.Format("Client send SendCollection2:\n{0}",CCollectionHelper.Collection2ToString(CollectionIn2)));

				Client.SendCollection3(CollectionIn3);
				Console.WriteLine(String.Format("Client send SendCollection3:\n{0}",CCollectionHelper.Collection3ToString(CollectionIn3)));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null && Client.State!=CommunicationState.Faulted)
				{
					Client.Close();
					Client=null;
				}
			}

			Console.WriteLine("Press any key to continue !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------