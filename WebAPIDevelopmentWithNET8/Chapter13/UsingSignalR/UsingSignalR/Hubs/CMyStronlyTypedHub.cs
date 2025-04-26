using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.SignalR;
//--------------------------------------------------------------------------------------------------------------------------------
namespace UsingSignalR
{
//--------------------------------------------------------------------------------------------------------------------------------
	// !!! Povoli sa iba AUTHORIZED COMMUNICATION.
	[Authorize]
	public sealed class CMyStronlyTypedHub : Hub<IMyClientInterface>
	{
//--------------------------------------------------------------------------------------------------------------------------------
	    public override async Task OnConnectedAsync()
		{
			Console.WriteLine("CONNECTION OPENED.");

			// !!! Vykona sa CLIENT METHOD, ktora notifikuje CLIENTS o prihlaseni noveho CLIENT.
			string												User=Context.User.Identity.Name;
			string												Message="CONNECTION OPENED.";

			// !!! Vykona sa CLIENT METHOD, ktora notifikuje CLIENTS o odhlaseni existujuceho CLIENT.
			await Clients.All.MyConnectionOpened(User,Message);

			await base.OnConnectedAsync();
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async override Task OnDisconnectedAsync(Exception Exception)
		{
			if (Exception!=null)
			{
				Console.WriteLine($"CONNECTION CLOSED - EXCEPTION [{Exception}].");
			}
			else
			{
				Console.WriteLine("CONNECTION CLOSED.");
			}

			// !!! Zoberie sa USER z CONTEXT.
			string												User=Context.User.Identity.Name;
			string												Message="CONNECTION CLOSED.";

			// !!! Vykona sa CLIENT METHOD, ktora notifikuje CLIENTS o odhlaseni existujuceho CLIENT.
			await Clients.All.MyConnectionClosed(User,Message);

			await base.OnDisconnectedAsync(Exception);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task MySendAddUserToGroup(string Group)
		{
			string												ConnectionID=Context.ConnectionId;
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendAddUserToGroup)}] CALLED. USER [{User}] GROUP [{Group}].");

			// !!! USER sa prida do GROUP.
			await Groups.AddToGroupAsync(ConnectionID,Group);

			// !!! Odosle sa notifikacia o pridani USER do GROUP.
			await Clients.Group(Group).MyAddUserToGroup(User,Group);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task MySendRemoveUserFromGroup(string Group)
		{
			string												ConnectionID=Context.ConnectionId;
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendRemoveUserFromGroup)}] CALLED. USER [{User}] GROUP [{Group}].");

			// !!! USER sa odoberie z GROUP.
			await Groups.RemoveFromGroupAsync(ConnectionID,Group);

			// !!! Odosle sa notifikacia o odobrani USER z GROUP.
			await Clients.Group(Group).MyRemoveUserFromGroup(User,Group);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public Task MySendMessage(string Message)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessage)}] CALLED. USER [{User}] MESSAGE [{Message}].");

			// !!! Odosle MESSAGE vsetkym CLIENTS.
			Task												SendTask=Clients.All.MyReceiveMessage(User,Message);

			return(SendTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<string> MySendMessageWithReturn(string Message)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessageWithReturn)}] CALLED. USER [{User}] MESSAGE [{Message}].");

			// !!! Odosle MESSAGE vsetkym CLIENTS.
			await Clients.All.MyReceiveMessage(User,Message);

			string												Result=$"METHOD FINISHED at TIME [{DateTime.Now}].";

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<string> MySendMessageToUser(string Message, string Username)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessageToUser)}] CALLED. USER [{User}] MESSAGE [{Message}] USERNAME [{Username}].");

			IMyClientInterface									Receiver=this.Clients.User(Username);

			if (Receiver!=null)
			{
				// !!! Odosle MESSAGE danemu USER.
				await Receiver.MyReceiveMessage(User,Message);

				string											Result=$"METHOD FINISHED at TIME [{DateTime.Now}].";

				return(Result);
			}
			else
			{
				string											Result=$"METHOD FINISHED at TIME [{DateTime.Now}].";

				return(Result);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task MySendMessageToGroup(string Group, string Message)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessageToGroup)}] CALLED. USER [{User}] GROUP [{Group}] MESSAGE [{Message}].");

			IMyClientInterface									Receiver=this.Clients.Group(Group);

			if (Receiver!=null)
			{
				// !!! Odosle MESSAGE danemu USER.
				await Receiver.MyReceiveMessage(User,Message);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------