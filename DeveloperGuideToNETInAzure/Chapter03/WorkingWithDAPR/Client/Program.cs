﻿//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	internal class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuWorkingWithDAPR								Menu=new CMenuWorkingWithDAPR();
			//CMenuServiceToServiceInvocation					Menu=new CMenuServiceToServiceInvocation();
			//CMenuStateManagement								Menu=new CMenuStateManagement();
			CMenuPublishSubscribe								Menu=new CMenuPublishSubscribe();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------