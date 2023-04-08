using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DCInterfaceLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDCInterfaceService : IDCInterfaceContract
	{
//-------------------------------------------------------------------------------------------------------
		public IName GetName()
		{
			return(new CFullName("Timmy","Anderson"));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendName(IName Name)
		{
			Console.WriteLine(string.Format("From client: {0}",Name.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------