using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CompositeDCLibrary
{
	public class CCompositeDCService : ICompositeDCContract
	{
//-------------------------------------------------------------------------------------------------------
		public CFriend GetFriend()
		{
			CName		Jenny=new CName("Jenny","Thompson");
			CName		Atreyu=new CName("Atreyu","No Name");
			CName		Timmy=new CName("Timmy","Anderson");
			CName[]		Friends=new CName[2]{Jenny,Atreyu};

			CFriend		Friend=new CFriend(Timmy,Friends);

			return(Friend);
		}
//-------------------------------------------------------------------------------------------------------
		public void SendFriend(CFriend Friend)
		{
			Console.WriteLine(string.Format("Friendship: {0}",Friend.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
	}
}
//-------------------------------------------------------------------------------------------------------