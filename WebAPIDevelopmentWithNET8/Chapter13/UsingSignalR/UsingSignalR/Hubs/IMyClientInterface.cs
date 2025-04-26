using System.Threading.Tasks;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//--------------------------------------------------------------------------------------------------------------------------------
	// !!!!! INTERFACE obsahuje vsetky METHODS, ktore implementuju CLIENTS a ktore moze SIGNAL R HUB volat.
	public interface IMyClientInterface
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD NAMES musia zodpovedat METHOD NAMES, ktore registruje CLIENT.
		Task MyConnectionOpened(string Sender, string Message);
		Task MyConnectionClosed(string Sender, string Message);
//--------------------------------------------------------------------------------------------------------------------------------
		Task MyReceiveMessage(string Sender, string Message);
		Task MyAddUserToGroup(string User, string Group);
		Task MyRemoveUserFromGroup(string User, string Group);
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------