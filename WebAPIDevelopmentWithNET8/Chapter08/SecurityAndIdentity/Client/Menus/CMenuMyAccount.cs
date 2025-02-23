using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
using SecurityAndIdentity;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMyAccount : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMyAccount()
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
				string											URL=$"{BASE_ADDRESS}MyAccount/Login";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClientOperationResponse					Response=CMyHttpClient.ExecuteMessage(Request);
				CMyTokenModel									TokenResponse=Response.Content.ConvertToObject<CMyTokenModel>();

				Token=TokenResponse.Token;
			}

			return(Token);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRegister(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												PhoneNumber=((string) Parameters[1]);
			string												Password=((string) Parameters[2]);
			CMyUserModel										RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/Register";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLogin(string CommandID, object[] Parameters)
		{
			string												UserName=((string) Parameters[0]);
			string												Password=((string) Parameters[1]);
			CMyLoginModel										RawContent=new CMyLoginModel(UserName,Password);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/Login";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRegisterFixed(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			CMyUserModel										RawContent;

			if (UserID==1)
			{
				string											UserName=CSecurityUsers.ADMINISTRATOR;
				string											PhoneNumber="12345678";
				string											Password="zy3pQjPDJB0yL3J&";
				
				RawContent=new CMyUserModel(UserName,PhoneNumber,Password);
			}
			else if (UserID==2)
			{
				string											UserName=CSecurityUsers.VIP;
				string											PhoneNumber="87654321";
				string											Password="Zy4pQjPDJB0yL3J+";

				RawContent=new CMyUserModel(UserName,PhoneNumber,Password);
			}
			else if (UserID==3)
			{
				string											UserName=CSecurityUsers.USER;
				string											PhoneNumber="56781234";
				string											Password="zY5pQjPDJB0yL3J&";
				
				RawContent=new CMyUserModel(UserName,PhoneNumber,Password);
			}
			else
			{
				Console.WriteLine("UNKNOWN USER.");
				return;
			}

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}MyAccount/Register";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);

		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginFixed(string CommandID, object[] Parameters)
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
		private void ExecuteCommandLoginSecureMethodAdministratorsOnly(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodAdministratorsOnly";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginSecureMethodUsersOrAdministrators(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodUsersOrAdministrators";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginSecureMethodUsersAndAdministrators(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodUsersAndAdministrators";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginSecureMethodVIPsOrAdministrators(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodVIPsOrAdministrators";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginSecureMethodVIPOnly(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodVIPOnly";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void SecureMethodAdministratorOrVIP(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodAdministratorOrVIP";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void SecureMethodPolicyAuthorizationAdministrator(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodPolicyAuthorizationAdministrator";
				CMyHttpClientHeaderAuthorization				HeaderAuthorization=new CMyHttpClientHeaderAuthorization("Bearer",Token);
				CMyHttpClientHeaders							Headers=new CMyHttpClientHeaders(new CMyHttpClientHeader[]{HeaderAuthorization});
				CMyHttpClientContent							Content=null;
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void SecureMethodPolicyAuthorizationAdministratorMultiHandler(string CommandID, object[] Parameters)
		{
			int													UserID=((int) Parameters[0]);
			string												Token=DoLogin(CommandID,UserID);

			if (Token!=null)
			{
				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_GET;
				string											URL=$"{BASE_ADDRESS}MySecure/SecureMethodPolicyAuthorizationAdministratorMultiHandler";
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

			CommandsCollection.Add(new CMenuCommand("1","REGISTER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandRegister));
			CommandsCollection.Add(new CMenuCommand("2","LOGIN",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING,EMenuCommandParameterType.E_STRING},ExecuteCommandLogin));
			CommandsCollection.Add(new CMenuCommand("3","REGISTER FIXED",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandRegisterFixed));
			CommandsCollection.Add(new CMenuCommand("4","LOGIN FIXED",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginFixed));
			CommandsCollection.Add(new CMenuCommand("5","SECURE METHOD ALL AUTHENTICATED USERS",new EMenuCommandParameterType[0],ExecuteCommandSecureMethodAllAuthenticatedUsers));
			CommandsCollection.Add(new CMenuCommand("6","ROLE - LOGIN + SECURE METHOD ALL AUTHENTICATED USERS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodAllAuthenticatedUsers));
			CommandsCollection.Add(new CMenuCommand("7","ROLE - LOGIN + SECURE METHOD ADMINISTRATORS ONLY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodAdministratorsOnly));
			CommandsCollection.Add(new CMenuCommand("8","ROLE - LOGIN + SECURE METHOD USERS OR ADMINISTRATORS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodUsersOrAdministrators));
			CommandsCollection.Add(new CMenuCommand("9","ROLE - LOGIN + SECURE METHOD USERS AND ADMINISTRATORS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodUsersAndAdministrators));
			CommandsCollection.Add(new CMenuCommand("10","ROLE - LOGIN + SECURE METHOD VIPS OR ADMINISTRATORS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodVIPsOrAdministrators));
			CommandsCollection.Add(new CMenuCommand("11","CLAIMS - LOGIN + SECURE METHOD VIP ONLY",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},ExecuteCommandLoginSecureMethodVIPOnly));
			CommandsCollection.Add(new CMenuCommand("12","CLAIMS - LOGIN + SECURE METHOD ADMINISTRATOR OR VIP",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},SecureMethodAdministratorOrVIP));
			CommandsCollection.Add(new CMenuCommand("13","POLICY - LOGIN + SECURE METHOD ADMINISTRATOR",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},SecureMethodPolicyAuthorizationAdministrator));
			CommandsCollection.Add(new CMenuCommand("14","POLICY - LOGIN + SECURE METHOD ADMINISTRATOR MULTI HANDLER",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_INT},SecureMethodPolicyAuthorizationAdministratorMultiHandler));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------