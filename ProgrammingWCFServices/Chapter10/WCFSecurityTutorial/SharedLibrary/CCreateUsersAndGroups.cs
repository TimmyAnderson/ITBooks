using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Security;
using System.ServiceModel.Description;
//-----------------------------------------------------------------------------
namespace SharedLibrary
{
//-----------------------------------------------------------------------------
	public static class CCreateUsersAndGroups
	{
//-----------------------------------------------------------------------------
		public static void CreateUsers()
		{
			MembershipCreateStatus	CMS;

			// Vytvorenie usera.
			Membership.Provider.CreateUser("Timmy","aaaaaa1+","someemail1@xxx.sk","Some question !","Some answer !",true,null,out CMS);

			Console.WriteLine(string.Format("User: {0} !",CMS.ToString()));

			// Vytvorenie usera.
			Membership.Provider.CreateUser("Atreyu","aaaaaa2+","someemail2@xxx.sk","Some question !","Some answer !",true,null,out CMS);

			Console.WriteLine(string.Format("User: {0} !",CMS.ToString()));

			// Vytvorenie usera.
			Membership.Provider.CreateUser("Jenny","aaaaaa3+","someemail3@xxx.sk","Some question !","Some answer !",true,null,out CMS);

			Console.WriteLine(string.Format("User: {0} !",CMS.ToString()));
		}
//-----------------------------------------------------------------------------
		public static void CreateRoles()
		{
			// Vytvorenie roly.
			Roles.Provider.CreateRole("Boys");

			// Pridanie usera do roly.
			Roles.Provider.AddUsersToRoles(new string[]{"Timmy"},new string[]{"Boys"});
			Roles.Provider.AddUsersToRoles(new string[]{"Atreyu"},new string[]{"Boys"});

			// Vytvorenie roly.
			Roles.Provider.CreateRole("Girls");

			// Pridanie usera do roly.
			Roles.Provider.AddUsersToRoles(new string[]{"Jenny"},new string[]{"Girls"});

			Console.WriteLine("Roles created !");
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------