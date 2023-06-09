using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DCHierarchyLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDCHierarchyService : IDCHierarchyContract
	{
//-------------------------------------------------------------------------------------------------------
		public CFullName GetName()
		{
			return(new CFullName("Timmy","Anderson"));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendFullName(CFullName Name)
		{
			Console.WriteLine(string.Format("Name: {0}",Name.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendName(CName Name)
		{
			Console.WriteLine(string.Format("Name: {0}",Name.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------