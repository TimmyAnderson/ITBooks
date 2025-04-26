using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http.Connections;
using Microsoft.AspNetCore.Http.Connections.Client;
using Microsoft.AspNetCore.SignalR.Client;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client1
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuSignalRClient : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE="MySendMessage";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE_WITH_RETURN="MySendMessageWithReturn";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_OPENED="MyConnectionOpened";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_CLOSED="MyConnectionClosed";
		private const string									METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE="MyReceiveMessage";
		private const string									METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP="MyAddUserToGroup";
		private const string									METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP="MyRemoveUserFromGroup";
//--------------------------------------------------------------------------------------------------------------------------------
		private HubConnection									MHubConnection;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuSignalRClient()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private string PerformLogin(string UserName, string Password)
		{
			CMyLoginModel										RawContent=new CMyLoginModel(UserName,Password);

			string												MessageID="LOGIN";
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/Login";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClientOperationResponse						Response=CMyHttpClient.ExecuteMessage(Request);

			if (Response.StatusCode==HttpStatusCode.OK)
			{
				CMyTokenModel									TokenResponse=Response.Content.ConvertToObject<CMyTokenModel>();
				string											Token=TokenResponse.Token;

				return(Token);
			}
			else
			{
				return(null);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task<string> MyAccessTokenProvider(string AccessToken)
		{
			Task<string>										Result=Task.FromResult(AccessToken);

			return(Result);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void MyConfigureConnection(HttpConnectionOptions Options, string AccessToken)
		{
			Options.AccessTokenProvider=(() => MyAccessTokenProvider(AccessToken));
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionReconnecting(Exception Exception)
		{
			if (Exception!=null)
			{
				Console.WriteLine($"EVENT - CONNECTION RECONNECTION - EXCEPTION [{Exception}].");
			}
			else
			{
				Console.WriteLine("EVENT - CONNECTION RECONNECTION.");
			}

			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionReconnected(string ConnectionID)
		{
			Console.WriteLine($"EVENT - CONNECTION RECONNECTED. CONNECTION ID [{ConnectionID}].");
			
			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionClosed(Exception Exception)
		{
			if (Exception!=null)
			{
				Console.WriteLine($"EVENT - CONNECTION CLOSED - EXCEPTION [{Exception}].");
			}
			else
			{
				Console.WriteLine("EVENT - CONNECTION CLOSED.");
			}

			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyConnectionOpened(string Sender, string Message)
		{
			Console.WriteLine($"!!! CONNECTION OPENED. SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyConnectionClosed(string Sender, string Message)
		{
			Console.WriteLine($"!!! CONNECTION CLOSED. SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyReceiveMessage(string Sender, string Message)
		{
			Console.WriteLine($"METHOD [{METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE}] CALLED. SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyAddUserToGroup(string User, string Group)
		{
			Console.WriteLine($"USER ADDED to GROUP. USER [{User}] GROUP [{Group}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyRemoveUserFromGroup(string User, string Group)
		{
			Console.WriteLine($"USER REMOVED from GROUP. USER [{User}] GROUP [{Group}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandNewConnection(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);

			if (MHubConnection==null)
			{
				string											AccessToken=PerformLogin(UserName,Password);

				if (AccessToken!=null && AccessToken!="")
				{
					HubConnectionBuilder						Builder=new HubConnectionBuilder();
					HttpTransportType							TransportTypes=(HttpTransportType.WebSockets | HttpTransportType.LongPolling);

					Builder.WithUrl($"{BASE_ADDRESS}MyHub",TransportTypes,P => MyConfigureConnection(P,AccessToken));

					MHubConnection=Builder.Build();

					MHubConnection.Reconnecting+=EventConnectionReconnecting;
					MHubConnection.Reconnected+=EventConnectionReconnected;
					MHubConnection.Closed+=EventConnectionClosed;

					MHubConnection.On<string,string>(METHOD_ID_CLIENT_MY_CONNECTION_OPENED,RemoteMethodMyConnectionOpened);
					MHubConnection.On<string,string>(METHOD_ID_CLIENT_MY_CONNECTION_CLOSED,RemoteMethodMyConnectionClosed);

					MHubConnection.On<string,string>(METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE,RemoteMethodMyReceiveMessage);
					MHubConnection.On<string,string>(METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP,RemoteMethodMyAddUserToGroup);
					MHubConnection.On<string,string>(METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP,RemoteMethodMyRemoveUserFromGroup);

					// !!! VALUE by mala byt rovnaka ako VALUE [TimeSpan HubOptions<THub>.KeepAliveInterval] na SERVER.
					MHubConnection.KeepAliveInterval=TimeSpan.FromSeconds(10);

					// !!! VALUE by mala byt rovnaka ako VALUE [TimeSpan HubOptions<THub>.ClientTimeoutInterval] na SERVER.
					MHubConnection.ServerTimeout=TimeSpan.FromSeconds(20);

					Console.WriteLine("CONNECTION CREATED.");
				}
				else
				{
					Console.WriteLine("Can't GET ACCESS TOKEN.");
				}
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT already exists.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDisposeConnection(string CommandID, object[] Parameters)
		{
			if (MHubConnection!=null)
			{
				MHubConnection.Remove(METHOD_ID_CLIENT_MY_CONNECTION_OPENED);
				MHubConnection.Remove(METHOD_ID_CLIENT_MY_CONNECTION_CLOSED);

				MHubConnection.Remove(METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE);
				MHubConnection.Remove(METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP);
				MHubConnection.Remove(METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP);

				MHubConnection.Reconnecting-=EventConnectionReconnecting;
				MHubConnection.Reconnected-=EventConnectionReconnected;
				MHubConnection.Closed-=EventConnectionClosed;

				MHubConnection.DisposeAsync().AsTask().Wait();

				MHubConnection=null;

				Console.WriteLine("CONNECTION DISPOSED.");
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT doesn't exist.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartConnection(string CommandID, object[] Parameters)
		{
			if (MHubConnection!=null)
			{
				HubConnectionState								State=MHubConnection.State;

				if (State==HubConnectionState.Disconnected)
				{
					MHubConnection.StartAsync().Wait();

					string										ConnectionID=MHubConnection.ConnectionId;

					Console.WriteLine($"CONNECTION STARTED. CONNECTION ID [{ConnectionID}].");
				}
				else
				{
					Console.WriteLine($"Can't START CONNECTION. STATE [{State}].");
				}
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT doesn't exist.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopConnection(string CommandID, object[] Parameters)
		{
			if (MHubConnection!=null)
			{
				HubConnectionState								State=MHubConnection.State;

				if (State==HubConnectionState.Connected)
				{
					string										ConnectionID=MHubConnection.ConnectionId;

					MHubConnection.StopAsync().Wait();

					Console.WriteLine($"CONNECTION STOPPED. CONNECTION ID [{ConnectionID}].");
				}
				else
				{
					Console.WriteLine($"Can't STOP CONNECTION. STATE [{State}].");
				}
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT doesn't exist.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInvokeMessage(string CommandID, object[] Parameters)
		{
			string												Message=(string)Parameters[0];

			if (MHubConnection!=null)
			{
				HubConnectionState								State=MHubConnection.State;

				if (State==HubConnectionState.Connected)
				{
					MHubConnection.InvokeAsync(METHOD_ID_SERVER_MY_SEND_MESSAGE,Message).Wait();

					Console.WriteLine("SERVER METHOD INVOKED.");
				}
				else
				{
					Console.WriteLine($"Can't SEND MESSAGE. STATE [{State}].");
				}
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT doesn't exist.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandInvokeMessageWithResult(string CommandID, object[] Parameters)
		{
			string												Message=(string)Parameters[0];

			if (MHubConnection!=null)
			{
				HubConnectionState								State=MHubConnection.State;

				if (State==HubConnectionState.Connected)
				{
					string										Result=MHubConnection.InvokeAsync<string>(METHOD_ID_SERVER_MY_SEND_MESSAGE_WITH_RETURN,Message).Result;

					Console.WriteLine($"SERVER METHOD INVOKED with RETURN VALUE [{Result}].");
				}
				else
				{
					Console.WriteLine($"Can't SEND MESSAGE. STATE [{State}].");
				}
			}
			else
			{
				Console.WriteLine("CONNECTION OBJECT doesn't exist.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("n","NEW CONNECTION OBJECT",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandNewConnection));
			CommandsCollection.Add(new CMenuCommand("d","DISPOSE CONNECTION OBJECT",new EMenuCommandParameterType[0],ExecuteCommandDisposeConnection));
			CommandsCollection.Add(new CMenuCommand("s","START CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandStartConnection));
			CommandsCollection.Add(new CMenuCommand("c","STOP CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandStopConnection));
			CommandsCollection.Add(new CMenuCommand("is","INVOKE MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandInvokeMessage));
			CommandsCollection.Add(new CMenuCommand("irs","INVOKE MESSAGE WITH RESULT",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandInvokeMessageWithResult));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------