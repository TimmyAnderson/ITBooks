using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http.Connections;
using Microsoft.AspNetCore.Http.Connections.Client;
using Microsoft.AspNetCore.SignalR.Client;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client1
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuSignalRMultiClient : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE="MySendMessage";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE_WITH_RETURN="MySendMessageWithReturn";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE_TO_USER="MySendMessageToUser";
		private const string									METHOD_ID_SERVER_MY_SEND_ADD_USER_TO_GROUP="MySendAddUserToGroup";
		private const string									METHOD_ID_SERVER_MY_SEND_REMOVE_USER_FROM_GROUP="MySendRemoveUserFromGroup";
		private const string									METHOD_ID_SERVER_MY_SEND_MESSAGE_TO_GROUP="MySendMessageToGroup";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_OPENED="MyConnectionOpened";
		private const string									METHOD_ID_CLIENT_MY_CONNECTION_CLOSED="MyConnectionClosed";
		private const string									METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE="MyReceiveMessage";
		private const string									METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP="MyAddUserToGroup";
		private const string									METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP="MyRemoveUserFromGroup";
//--------------------------------------------------------------------------------------------------------------------------------
		private readonly Dictionary<string,CHubConnectionData>	MHubConnections;
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuSignalRMultiClient()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
			MHubConnections=new Dictionary<string,CHubConnectionData>();
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
		private void MyConfigureLogging(ILoggingBuilder Logging)
		{
			// !!! Nastavi sa LOG LEVEL.
			Logging.SetMinimumLevel(LogLevel.Debug);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void MyConfigureHubConnectionOptions(HubConnectionOptions Options)
		{
			Options.StatefulReconnectBufferSize=200000;
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionReconnecting(Exception Exception)
		{
			if (Exception!=null)
			{
				Console.WriteLine($"!!!!!!!!!! EVENT - CONNECTION RECONNECTION - EXCEPTION [{Exception.Message}].");
			}
			else
			{
				Console.WriteLine("!!!!!!!!!! EVENT - CONNECTION RECONNECTION.");
			}

			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionReconnected(string ConnectionID)
		{
			Console.WriteLine($"!!!!!!!!!! EVENT - CONNECTION RECONNECTED. CONNECTION ID [{ConnectionID}].");
			
			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private Task EventConnectionClosed(Exception Exception)
		{
			if (Exception!=null)
			{
				Console.WriteLine($"!!!!!!!!!! EVENT - CONNECTION CLOSED - EXCEPTION [{Exception.Message}].");
			}
			else
			{
				Console.WriteLine("!!!!!!!!!! EVENT - CONNECTION CLOSED.");
			}

			Task												CompletedTask=Task.CompletedTask;

			return(CompletedTask);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyConnectionOpened(CHubConnectionData ConnectionData, string Sender, string Message)
		{
			string												ConnectionID=ConnectionData.HubConnection.ConnectionId;
			string												Receiver=ConnectionData.UserName;

			Console.WriteLine($"!!! CONNECTION OPENED. ID [{ConnectionID}] RECEIVER [{Receiver}] SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyConnectionClosed(CHubConnectionData ConnectionData, string Sender, string Message)
		{
			string												ConnectionID=ConnectionData.HubConnection.ConnectionId;
			string												Receiver=ConnectionData.UserName;

			Console.WriteLine($"!!! CONNECTION CLOSED. ID [{ConnectionID}] RECEIVER [{Receiver}] SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyReceiveMessage(CHubConnectionData ConnectionData, string Sender, string Message)
		{
			string												ConnectionID=ConnectionData.HubConnection.ConnectionId;
			string												Receiver=ConnectionData.UserName;

			Console.WriteLine($"METHOD [{METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE}] CALLED. ID [{ConnectionID}] RECEIVER [{Receiver}] SENDER [{Sender}] MESSAGE [{Message}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyAddUserToGroup(CHubConnectionData ConnectionData, string User, string Group)
		{
			string												ConnectionID=ConnectionData.HubConnection.ConnectionId;
			string												Receiver=ConnectionData.UserName;

			Console.WriteLine($"USER ADDED to GROUP. ID [{ConnectionID}] RECEIVER [{Receiver}] USER [{User}] GROUP [{Group}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void RemoteMethodMyRemoveUserFromGroup(CHubConnectionData ConnectionData, string User, string Group)
		{
			string												ConnectionID=ConnectionData.HubConnection.ConnectionId;
			string												Receiver=ConnectionData.UserName;

			Console.WriteLine($"USER REMOVED from GROUP. ID [{ConnectionID}] RECEIVER [{Receiver}] USER [{User}] GROUP [{Group}].");
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandListConnections(string CommandID, object[] Parameters)
		{
			string[]											ConnectionNames=MHubConnections.Keys.ToArray();

			for(int Index=0;Index<ConnectionNames.Length;Index++)
			{
				string											ConnectionName=ConnectionNames[Index];
				CHubConnectionData								ConnectionData=MHubConnections[ConnectionName];
				string											ConnectionUser=ConnectionData.UserName;
				HubConnection									Connection=ConnectionData.HubConnection;
				string											ConnectionID=Connection.ConnectionId;
				HubConnectionState								ConnectionState=Connection.State;

				Console.WriteLine($"NAME [{ConnectionName}] USER [{ConnectionUser}] ID [{ConnectionID}] STATE [{ConnectionState}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandNewConnection(string CommandID, object[] Parameters)
		{
			string												ConnectionName=(string)Parameters[0];
			string												UserName=((string) Parameters[1]);
			string												Password=((string) Parameters[2]);

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData==null)
			{
				string											AccessToken=PerformLogin(UserName,Password);

				if (AccessToken!=null && AccessToken!="")
				{
					HubConnectionBuilder						Builder=new HubConnectionBuilder();
					HttpTransportType							TransportTypes=(HttpTransportType.WebSockets | HttpTransportType.LongPolling);

					// !!! Nastavi sa URL SERVER HUB.
					Builder.WithUrl($"{BASE_ADDRESS}MyHub",TransportTypes,P => MyConfigureConnection(P,AccessToken));

					// !!! Nastavi sa automaticky RECONNECT.
					Builder.WithAutomaticReconnect(new TimeSpan[]{TimeSpan.FromSeconds(0),TimeSpan.FromSeconds(15),TimeSpan.FromSeconds(30),TimeSpan.FromSeconds(60)});

					// !!! Povoli sa STATEFUL RECONNECT.
					Builder.WithStatefulReconnect();

					// !!! Nastavia sa SETTIONS pre HUB CONNECTION.
					Builder.Services.Configure<HubConnectionOptions>(MyConfigureHubConnectionOptions);

					Builder.ConfigureLogging(MyConfigureLogging);

					HubConnection								HubConnection=Builder.Build();

					HubConnectionData=new CHubConnectionData(UserName,HubConnection);

					HubConnection.Reconnecting+=EventConnectionReconnecting;
					HubConnection.Reconnected+=EventConnectionReconnected;
					HubConnection.Closed+=EventConnectionClosed;

					HubConnection.On<string,string>(METHOD_ID_CLIENT_MY_CONNECTION_OPENED,(P1,P2) => RemoteMethodMyConnectionOpened(HubConnectionData,P1,P2));
					HubConnection.On<string,string>(METHOD_ID_CLIENT_MY_CONNECTION_CLOSED,(P1,P2) => RemoteMethodMyConnectionClosed(HubConnectionData,P1,P2));

					HubConnection.On<string,string>(METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE,(P1,P2) => RemoteMethodMyReceiveMessage(HubConnectionData,P1,P2));
					HubConnection.On<string,string>(METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP,(P1,P2) => RemoteMethodMyAddUserToGroup(HubConnectionData,P1,P2));
					HubConnection.On<string,string>(METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP,(P1,P2) => RemoteMethodMyRemoveUserFromGroup(HubConnectionData,P1,P2));

					// !!! VALUE by mala byt rovnaka ako VALUE [TimeSpan HubOptions<THub>.KeepAliveInterval] na SERVER.
					HubConnection.KeepAliveInterval=TimeSpan.FromSeconds(10);

					// !!! VALUE by mala byt rovnaka ako VALUE [TimeSpan HubOptions<THub>.ClientTimeoutInterval] na SERVER.
					HubConnection.ServerTimeout=TimeSpan.FromSeconds(20);

					MHubConnections.Add(ConnectionName,HubConnectionData);

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
			string												ConnectionName=(string)Parameters[0];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;

				HubConnection.Remove(METHOD_ID_CLIENT_MY_CONNECTION_OPENED);
				HubConnection.Remove(METHOD_ID_CLIENT_MY_CONNECTION_CLOSED);

				HubConnection.Remove(METHOD_ID_CLIENT_MY_RECEIVE_MESSAGE);
				HubConnection.Remove(METHOD_ID_CLIENT_MY_ADD_USER_TO_GROUP);
				HubConnection.Remove(METHOD_ID_CLIENT_MY_REMOVE_USER_FROM_GROUP);

				HubConnection.Reconnecting-=EventConnectionReconnecting;
				HubConnection.Reconnected-=EventConnectionReconnected;
				HubConnection.Closed-=EventConnectionClosed;

				HubConnection.DisposeAsync().AsTask().Wait();

				MHubConnections.Remove(ConnectionName);

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
			string												ConnectionName=(string)Parameters[0];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Disconnected)
				{
					HubConnection.StartAsync().Wait();

					string										ConnectionID=HubConnection.ConnectionId;

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
			string												ConnectionName=(string)Parameters[0];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					string										ConnectionID=HubConnection.ConnectionId;

					HubConnection.StopAsync().Wait();

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
			string												ConnectionName=(string)Parameters[0];
			string												Message=(string)Parameters[1];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					HubConnection.InvokeAsync(METHOD_ID_SERVER_MY_SEND_MESSAGE,Message).Wait();

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
			string												ConnectionName=(string)Parameters[0];
			string												Message=(string)Parameters[1];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					string										Result=HubConnection.InvokeAsync<string>(METHOD_ID_SERVER_MY_SEND_MESSAGE_WITH_RETURN,Message).Result;

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
		private void ExecuteCommandInvokeMessageToUser(string CommandID, object[] Parameters)
		{
			string												ConnectionName=(string)Parameters[0];
			string												Message=(string)Parameters[1];
			string												Receiver=(string)Parameters[2];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					string										Result=HubConnection.InvokeAsync<string>(METHOD_ID_SERVER_MY_SEND_MESSAGE_TO_USER,Message,Receiver).Result;

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
		private void ExecuteCommandSendMessageToGroup(string CommandID, object[] Parameters)
		{
			string												ConnectionName=(string)Parameters[0];
			string												Group=(string)Parameters[1];
			string												Message=(string)Parameters[2];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					HubConnection.InvokeAsync(METHOD_ID_SERVER_MY_SEND_MESSAGE_TO_GROUP,Group,Message).Wait();

					Console.WriteLine($"MESSAGE SENT to GROUP [{Group}].");
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
		private void ExecuteCommandSendAddUserToGroup(string CommandID, object[] Parameters)
		{
			string												ConnectionName=(string)Parameters[0];
			string												Group=(string)Parameters[1];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;
				
				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					HubConnection.InvokeAsync(METHOD_ID_SERVER_MY_SEND_ADD_USER_TO_GROUP,Group).Wait();

					Console.WriteLine($"SERVER METHOD ADD TO GROUP CALLED.");
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
		private void ExecuteCommandSendRemoveUserFromGroup(string CommandID, object[] Parameters)
		{
			string												ConnectionName=(string)Parameters[0];
			string												Group=(string)Parameters[1];

			CHubConnectionData									HubConnectionData;
				
			MHubConnections.TryGetValue(ConnectionName,out HubConnectionData);

			if (HubConnectionData!=null)
			{
				HubConnection									HubConnection=HubConnectionData.HubConnection;
				HubConnectionState								State=HubConnection.State;

				if (State==HubConnectionState.Connected || State==HubConnectionState.Reconnecting)
				{
					HubConnection.InvokeAsync(METHOD_ID_SERVER_MY_SEND_REMOVE_USER_FROM_GROUP,Group).Wait();

					Console.WriteLine($"SERVER METHOD REMOVE FROM GROUP CALLED.");
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
		private void ExecuteCommandSendMessageViaRest(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);
			string												Sender=(string)Parameters[2];
			string												Message=(string)Parameters[3];

			string												AccessToken=PerformLogin(UserName,Password);
			
			if (AccessToken!=null && AccessToken!="")
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MyHubGateway/SendMessageViaSignalR?Sender={Sender}&Message={Message}";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",AccessToken);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
			else
			{
				Console.WriteLine("Can't GET ACCESS TOKEN.");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandNewConnections(string CommandID, object[] Parameters)
		{
			ExecuteCommandNewConnection(CommandID,new object[]{"1",CMySettings.USER_1_USERNAME,CMySettings.USER_1_PASSWORD});
			ExecuteCommandNewConnection(CommandID,new object[]{"2",CMySettings.USER_2_USERNAME,CMySettings.USER_2_PASSWORD});
			ExecuteCommandNewConnection(CommandID,new object[]{"3",CMySettings.USER_1_USERNAME,CMySettings.USER_1_PASSWORD});
			ExecuteCommandNewConnection(CommandID,new object[]{"4",CMySettings.USER_2_USERNAME,CMySettings.USER_2_PASSWORD});
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandDisposeConnections(string CommandID, object[] Parameters)
		{
			ExecuteCommandDisposeConnection(CommandID,new object[]{"1"});
			ExecuteCommandDisposeConnection(CommandID,new object[]{"2"});
			ExecuteCommandDisposeConnection(CommandID,new object[]{"3"});
			ExecuteCommandDisposeConnection(CommandID,new object[]{"4"});
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStartConnections(string CommandID, object[] Parameters)
		{
			ExecuteCommandStartConnection(CommandID,new object[]{"1"});
			ExecuteCommandStartConnection(CommandID,new object[]{"2"});
			ExecuteCommandStartConnection(CommandID,new object[]{"3"});
			ExecuteCommandStartConnection(CommandID,new object[]{"4"});
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandStopConnections(string CommandID, object[] Parameters)
		{
			ExecuteCommandStopConnection(CommandID,new object[]{"1"});
			ExecuteCommandStopConnection(CommandID,new object[]{"2"});
			ExecuteCommandStopConnection(CommandID,new object[]{"3"});
			ExecuteCommandStopConnection(CommandID,new object[]{"4"});
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandAddUsersToGroups(string CommandID, object[] Parameters)
		{
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"1",CMySettings.GROUP_ALL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"2",CMySettings.GROUP_ALL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"3",CMySettings.GROUP_ALL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"4",CMySettings.GROUP_ALL});

			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"1",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"2",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"3",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendAddUserToGroup(CommandID,new object[]{"4",CMySettings.GROUP_LOCAL});
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRemoveUsersFromGroups(string CommandID, object[] Parameters)
		{
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"1",CMySettings.GROUP_ALL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"2",CMySettings.GROUP_ALL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"3",CMySettings.GROUP_ALL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"4",CMySettings.GROUP_ALL});

			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"1",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"2",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"3",CMySettings.GROUP_LOCAL});
			ExecuteCommandSendRemoveUserFromGroup(CommandID,new object[]{"4",CMySettings.GROUP_LOCAL});
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("l","LIST CONNECTION OBJECTS",new EMenuCommandParameterType[0],ExecuteCommandListConnections));
			CommandsCollection.Add(new CMenuCommand("n","NEW CONNECTION OBJECT",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandNewConnection));
			CommandsCollection.Add(new CMenuCommand("d","DISPOSE CONNECTION OBJECT",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandDisposeConnection));
			CommandsCollection.Add(new CMenuCommand("s","START CONNECTION",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandStartConnection));
			CommandsCollection.Add(new CMenuCommand("c","STOP CONNECTION",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandStopConnection));
			CommandsCollection.Add(new CMenuCommand("is","INVOKE MESSAGE",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInvokeMessage));
			CommandsCollection.Add(new CMenuCommand("irs","INVOKE MESSAGE WITH RESULT",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInvokeMessageWithResult));
			CommandsCollection.Add(new CMenuCommand("iu","INVOKE MESSAGE TO USER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandInvokeMessageToUser));
			CommandsCollection.Add(new CMenuCommand("sg","SEND MESSAGE TO GROUP",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessageToGroup));

			CommandsCollection.Add(new CMenuCommand("ag","ADD USER TO GROUP",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendAddUserToGroup));
			CommandsCollection.Add(new CMenuCommand("rg","REMOVE USER FROM GROUP",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendRemoveUserFromGroup));

			CommandsCollection.Add(new CMenuCommand("r","SEND MESSAGE VIA REST",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandSendMessageViaRest));

			CommandsCollection.Add(new CMenuCommand("xn","NEW CONNECTION OBJECTS",new EMenuCommandParameterType[0],ExecuteCommandNewConnections));
			CommandsCollection.Add(new CMenuCommand("xd","DISPOSE CONNECTION OBJECTS",new EMenuCommandParameterType[0],ExecuteCommandDisposeConnections));
			CommandsCollection.Add(new CMenuCommand("xs","START CONNECTIONS",new EMenuCommandParameterType[0],ExecuteCommandStartConnections));
			CommandsCollection.Add(new CMenuCommand("xc","STOP CONNECTIONS",new EMenuCommandParameterType[0],ExecuteCommandStopConnections));

			CommandsCollection.Add(new CMenuCommand("xag","ADD USERS TO GROUPS",new EMenuCommandParameterType[0],ExecuteCommandAddUsersToGroups));
			CommandsCollection.Add(new CMenuCommand("xrg","REMOVE USERS FROM GROUPS",new EMenuCommandParameterType[0],ExecuteCommandRemoveUsersFromGroups));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------