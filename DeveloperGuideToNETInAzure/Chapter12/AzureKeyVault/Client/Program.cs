//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class Program
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public static void Main(string[] args)
		{
//			CMenuSystemAssignedManagedIdentityLocal				Menu=new CMenuSystemAssignedManagedIdentityLocal();
//			CMenuUserAssignedManagedIdentityLocal				Menu=new CMenuUserAssignedManagedIdentityLocal();
//			CMenuSystemAssignedManagedIdentityDockerLocal		Menu=new CMenuSystemAssignedManagedIdentityDockerLocal();
//			CMenuUserAssignedManagedIdentityDockerLocal			Menu=new CMenuUserAssignedManagedIdentityDockerLocal();
//			CMenuSystemAssignedManagedIdentityAzure				Menu=new CMenuSystemAssignedManagedIdentityAzure();
			CMenuUserAssignedManagedIdentityAzure				Menu=new CMenuUserAssignedManagedIdentityAzure();

			Menu.Execute();
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------