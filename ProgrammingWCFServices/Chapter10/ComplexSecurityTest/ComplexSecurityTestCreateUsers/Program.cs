using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.ServiceModel.Description;
using System.ServiceModel.Security;
using System.Web.Security;
//-------------------------------------------------------------------------------------------------------
namespace ComplexSecurityTestCreateUsers
{
//-------------------------------------------------------------------------------------------------------
	class Program
	{
//-------------------------------------------------------------------------------------------------------
		static void CreateUsers()
		{
			MembershipCreateStatus	CMS;

			// Zmazem existujucich USERS - ak existuju.
			Membership.Provider.DeleteUser("Timmy",true);
			Membership.Provider.DeleteUser("Atreyu",true);
			Membership.Provider.DeleteUser("Jenny",true);

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
//-------------------------------------------------------------------------------------------------------
		static void CreateRoles()
		{
			// Zmazem existujuce ROLES - ak existuju.
			Roles.Provider.DeleteRole("Boys",false);
			Roles.Provider.DeleteRole("Girls",false);

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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			try
			{
				CreateUsers();
				CreateRoles();
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: {0} !",E.Message));
			}

			Console.WriteLine("Press any key to EXIT !");
			Console.ReadLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------