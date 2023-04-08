using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using WCFToWCFCollectionsAutomaticClient.CWCFToWCFCollectionsProxy;
//-------------------------------------------------------------------------------------------------------
namespace WCFToWCFCollectionsAutomaticClient
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

			WCFToWCFCollectionsContractClient	Client=null;
			List<CName>							CollectionIn1=CCollectionHelper.GetCollection1();
			Dictionary<int,CName>				CollectionIn2=CCollectionHelper.GetCollection2();
			CMyCollection_CName					CollectionIn3=CCollectionHelper.GetCollection3();
			List<CName>							CollectionOut1=null;
			Dictionary<int,CName>				CollectionOut2=null;
			CMyCollection_CName					CollectionOut3=null;

			try
			{
				Client=new WCFToWCFCollectionsContractClient("NetTcpBinding_IWCFToWCFCollectionsContract");

				// V proxy reprezentovana collection ako pole.
				CName[]							Array1=Client.GetCollection1();

				CollectionOut1=new List<CName>(Array1);
				Console.WriteLine(String.Format("Server returned GetCollection1():\n{0}",CCollectionHelper.Collection1ToString(CollectionOut1)));

				CollectionOut2=Client.GetCollection2();
				Console.WriteLine(String.Format("Server returned GetCollection2():\n{0}",CCollectionHelper.Collection2ToString(CollectionOut2)));

				CollectionOut3=Client.GetCollection3();
				Console.WriteLine(String.Format("Server returned GetCollection3():\n{0}",CCollectionHelper.Collection3ToString(CollectionOut3)));

				// V proxy reprezentovana collection ako pole.
				CName[]							Array2=CollectionIn1.ToArray();

				Client.SendCollection1(Array2);
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