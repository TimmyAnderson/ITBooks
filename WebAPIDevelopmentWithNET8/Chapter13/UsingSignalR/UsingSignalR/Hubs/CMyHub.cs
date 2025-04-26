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
	public sealed class CMyHub : Hub
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE="MyReceiveMessage";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_OPENED="MyConnectionOpened";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_CLOSED="MyConnectionClosed";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
	    public override async Task OnConnectedAsync()
		{
			Console.WriteLine("CONNECTION OPENED.");

			// !!! Vykona sa CLIENT METHOD, ktora notifikuje CLIENTS o prihlaseni noveho CLIENT.
			string												User=Context.User.Identity.Name;
			string												Message="CONNECTION OPENED.";

			// !!! Vykona sa CLIENT METHOD, ktora notifikuje CLIENTS o odhlaseni existujuceho CLIENT.
			await Clients.All.SendAsync(METHOD_ID_CLIENT_MY_CONNECTION_OPENED,User,Message);

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
			await Clients.All.SendAsync(METHOD_ID_CLIENT_MY_CONNECTION_CLOSED,User,Message);

			await base.OnDisconnectedAsync(Exception);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public Task MySendMessage(string Message)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessage)}] CALLED. USER [{User}] MESSAGE [{Message}].");

			string												MethodName=METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE;

			// !!! Odosle MESSAGE vsetkym CLIENTS.
			Task												SendTask=Clients.All.SendAsync(MethodName,User,Message);

			return(SendTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<string> MySendMessageWithReturn(string Message)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessageWithReturn)}] CALLED. USER [{User}] MESSAGE [{Message}].");

			string												MethodName=METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE;

			// !!! Odosle MESSAGE vsetkym CLIENTS.
			await Clients.All.SendAsync(MethodName,User,Message);

			string												Result=$"METHOD FINISHED at TIME [{DateTime.Now}].";

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		public async Task<string> MySendMessageToUser(string Message, string Username)
		{
			string												User=Context.User.Identity.Name;

			Console.WriteLine($"METHOD [{nameof(MySendMessageToUser)}] CALLED. USER [{User}] MESSAGE [{Message}] USERNAME [{Username}].");

			IClientProxy										Receiver=this.Clients.User(Username);

			if (Receiver!=null)
			{
				string											MethodName=METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE;

				// !!! Odosle MESSAGE danemu USER.
				await Receiver.SendAsync(MethodName,User,Message);

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
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------