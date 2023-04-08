using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CDCCollectionsLibrary;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsManualClient
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

			CCDCCollectionsProxy				Client=null;
			CMyCollection<CName>				CollectionIn=CCollectionHelper.GetCollection();
			CMyCollection<CName>				CollectionOut=null;

			// Tento objekt by sa dal dalej konfigurovat napriklad pre pouzitie transakcii.
			Binding								TCPBinding=new NetTcpBinding();

			try
			{
				Client=new CCDCCollectionsProxy(TCPBinding,"net.tcp://localhost:9001/ICDCCollectionsContract");

				CollectionOut=Client.GetCollection();
				Console.WriteLine(String.Format("Server returned GetCollection():\n{0}",CCollectionHelper.CollectionToString(CollectionOut)));

				Client.SendCollection(CollectionIn);
				Console.WriteLine(String.Format("Client send SendCollection3:\n{0}",CCollectionHelper.CollectionToString(CollectionIn)));
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