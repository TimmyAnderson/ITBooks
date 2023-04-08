using System;
using System.Collections.Generic;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace VersionRoundTripLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CVersionRoundTripService : IVersionRoundTripContract
	{
//-------------------------------------------------------------------------------------------------------
		public CServerNameWithoutEDO DoRoundTripWithoutEDO(CServerNameWithoutEDO Name)
		{
			Console.WriteLine(string.Format("From client: {0}",Name.ToString()));

			CServerNameWithoutEDO	NewServerName=new CServerNameWithoutEDO(Name.FirstName,Name.LastName);

			return(NewServerName);
		}
//-------------------------------------------------------------------------------------------------------
		public CServerNameWithEDO DoRoundTripWithEDO(CServerNameWithEDO Name)
		{
			Console.WriteLine(string.Format("From client: {0}",Name.ToString()));

			CServerNameWithEDO		NewServerName=new CServerNameWithEDO(Name.FirstName,Name.LastName,Name.ExtensionData);

			return(NewServerName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------