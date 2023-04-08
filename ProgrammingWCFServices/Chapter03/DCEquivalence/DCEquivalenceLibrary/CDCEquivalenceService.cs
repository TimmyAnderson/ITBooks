using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DCEquivalenceLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CDCEquivalenceService : IDCEquivalenceContract
	{
//-------------------------------------------------------------------------------------------------------
		public CServerPerson GetPerson()
		{
			return(new CServerPerson("Timmy","Anderson",12));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendPerson(CServerPerson Person)
		{
			Console.WriteLine(string.Format("From client: {0}",Person.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
		public CServerErrorPerson GetErrorPerson()
		{
			return(new CServerErrorPerson("Timmy","Anderson",12));
		}
//-------------------------------------------------------------------------------------------------------
		public void SendErrorPerson(CServerErrorPerson Person)
		{
			Console.WriteLine(string.Format("From client: {0}",Person.ToString()));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------