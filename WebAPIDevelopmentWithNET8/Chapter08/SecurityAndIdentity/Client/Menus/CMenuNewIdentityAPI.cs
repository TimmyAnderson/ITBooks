using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
using NewIdentityAPI;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuNewIdentityAPI : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuNewIdentityAPI()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private string DoLogin(string CommandID, int UserID)
		{
			CMyLoginModel										RawContent;

			if (UserID==1)
			{
				string											UserName=CSecurityUsers.ADMINISTRATOR;
				string											Password="zy3pQjPDJB0yL3J&";
				
				RawContent=new CMyLoginModel(UserName,Password);
			}
			else if (UserID==2)
			{
				string											UserName=CSecurityUsers.VIP;
				string											Password="Zy4pQjPDJB0yL3J+";

				RawContent=new CMyLoginModel(UserName,Password);
			}
			else if (UserID==3)
			{
				string											UserName=CSecurityUsers.USER;
				string											Password="zY5pQjPDJB0yL3J&";

				RawContent=new CMyLoginModel(UserName,Password);
			}
			else
			{
				Console.WriteLine("UNKNOWN USER.");
				return(null);
			}

			string												Token;

			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_POST;
				string											URL=$"{BASE_ADDRESS}MyAccount/login";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClientOperationResponse					Response=CMyHttpClient.ExecuteMessage(Request);
				CMyTokenModel									TokenResponse=Response.Content.ConvertToObject<CMyTokenModel>();

				Token=TokenResponse.AccessToken;
			}

			return(Token);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRegister(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			CMyUserModel										RawContent;

			if (UserID==1)
			{
				string											UserName=CSecurityUsers.ADMINISTRATOR;
				string											Password="zy3pQjPDJB0yL3J&";
				
				RawContent=new CMyUserModel(UserName,Password);
			}
			else if (UserID==2)
			{
				string											UserName=CSecurityUsers.VIP;
				string											Password="Zy4pQjPDJB0yL3J+";

				RawContent=new CMyUserModel(UserName,Password);
			}
			else if (UserID==3)
			{
				string											UserName=CSecurityUsers.USER;
				string											Password="zY5pQjPDJB0yL3J&";
				
				RawContent=new CMyUserModel(UserName,Password);
			}
			else
			{
				Console.WriteLine("UNKNOWN USER.");
				return;
			}

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/register";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);

		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLogin(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);

			DoLogin(CommandID,UserID);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandSecureMethodAllAuthenticatedUsers(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}MySecure/SecureMethodAllAuthenticatedUsers";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginSecureMethodAllAuthenticatedUsers(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodAllAuthenticatedUsers";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","REGISTER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandRegister));
			CommandsCollection.Add(new CMenuCommand("2","LOGIN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLogin));
			CommandsCollection.Add(new CMenuCommand("3","SECURE METHOD ALL AUTHENTICATED USERS",new EMenuCommandParameterType[0],ExecuteCommandSecureMethodAllAuthenticatedUsers));
			CommandsCollection.Add(new CMenuCommand("4","ROLE - LOGIN + SECURE METHOD ALL AUTHENTICATED USERS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodAllAuthenticatedUsers));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------