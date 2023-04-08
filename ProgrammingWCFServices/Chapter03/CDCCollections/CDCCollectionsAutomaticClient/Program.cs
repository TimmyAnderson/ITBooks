using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using CDCCollectionsAutomaticClient.CCDCCollectionsProxy;
//-------------------------------------------------------------------------------------------------------
namespace CDCCollectionsAutomaticClient
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

			CDCCollectionsContractClient		Client=null;
			CMyCollection_CName					CollectionIn=CCollectionHelper.GetCollection();
			CMyCollection_CName					CollectionOut=null;

			try
			{
				Client=new CDCCollectionsContractClient("NetTcpBinding_ICDCCollectionsContract");

				CollectionOut=Client.GetCollection();
				Console.WriteLine(String.Format("Server returned GetCollection():\n{0}",CCollectionHelper.CollectionToString(CollectionOut)));

				Client.SendCollection(CollectionIn);
				Console.WriteLine(String.Format("Client send SendCollection:\n{0}",CCollectionHelper.CollectionToString(CollectionIn)));
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