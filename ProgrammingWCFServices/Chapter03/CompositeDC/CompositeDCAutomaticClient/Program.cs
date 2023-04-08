using System;
using System.Collections.Generic;
using System.Text;
using CompositeDCAutomaticClient.CCompositeDCProxy;
//-------------------------------------------------------------------------------------------------------
namespace CompositeDCAutomaticClient
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static string CNameDCToString(CName Name)
		{
			return(string.Format("CName - FirstName: {0}, LastName: {1} !",Name.FirstName, Name.LastName));
		}
//-------------------------------------------------------------------------------------------------------
		static string CFriendDCToString(CFriend Friend)
		{
			StringBuilder		SB=new StringBuilder();

			SB.AppendLine(string.Format("CFriend - MyName: {0}",Friend.MyName.ToString()));
			
			for(int i=0;i<Friend.Friends.Length;i++)
				SB.AppendLine(string.Format("   Friend {0} - {1}",i+1,CNameDCToString(Friend.Friends[i])));

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="CLIENT";

			Console.WriteLine("Press any key to START !");
			Console.ReadLine();

			CompositeDCContractClient			Client=null;
			CName								Jenny=new CName();
			CName								Atreyu=new CName();
			CName								Timmy=new CName();
			CName[]								Friends=new CName[2]{Atreyu,Timmy};
			CFriend								Friend=new CFriend();

			// Vygenerovane proxy ma iba default constructor.
			Jenny.FirstName="Jenny";
			Jenny.LastName="Thompson";
			Atreyu.FirstName="Atreyu";
			Atreyu.LastName="No Name";
			Timmy.FirstName="Timmy";
			Timmy.LastName="Anderson";

			Friend.MyName=Jenny;
			Friend.Friends=Friends;

			try
			{
				Client=new CompositeDCContractClient("NetTcpBinding_ICompositeDCContract");

				Client.SendFriend(Friend);
				Console.WriteLine(String.Format("Client send this friendship: {0}",CFriendDCToString(Friend)));
				Console.WriteLine(String.Format("Server returned this friendship: {0}",CFriendDCToString(Client.GetFriend())));
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
			finally
			{
				if (Client!=null)
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