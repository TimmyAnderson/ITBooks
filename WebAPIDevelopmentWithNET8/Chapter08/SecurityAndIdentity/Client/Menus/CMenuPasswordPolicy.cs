using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MySharedLibrary;
using SecurityAndIdentity;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuPasswordPolicy : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		private const string									BASE_ADDRESS="https://localhost:7000/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuPasswordPolicy()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRegisterPasswordOK(string CommandID, object[] Parameters)
		{
			string												UserName="MyUser1";
			string												PhoneNumber="12345678";
			string												Password="zy3pQjPDJB0yL3J&";
			CMyUserModel										RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}PasswordPolicy/Register";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);

		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandRegisterPasswordWrong(string CommandID, object[] Parameters)
		{
			string												UserName="MyUser2";
			string												PhoneNumber="12345678";
			string												Password="xxx";
			CMyUserModel										RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}PasswordPolicy/Register";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);

		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginOK(string CommandID, object[] Parameters)
		{
			string												UserName="MyUser1";
			string												PhoneNumber="12345678";
			string												Password="zy3pQjPDJB0yL3J&";
			CMyUserModel										RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}PasswordPolicy/Login";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandLoginWithLockout(string CommandID, object[] Parameters)
		{
			// !!! Pouzije sa 3 krat INVALID PASSWORD.
			for(int Index=0;Index<3;Index++)
			{
				string											UserName="MyUser1";
				string											PhoneNumber="12345678";
				string											Password="xxx";
				CMyUserModel									RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_POST;
				string											URL=$"{BASE_ADDRESS}PasswordPolicy/Login";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}

			// !!! ACCOUNT je LOCKED, takze nejde prihlasenie ani s VALID PASSWORD.

			{
				string											UserName="MyUser1";
				string											PhoneNumber="12345678";
				string											Password="zy3pQjPDJB0yL3J&";
				CMyUserModel									RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_POST;
				string											URL=$"{BASE_ADDRESS}PasswordPolicy/Login";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
				TimeSpan										Timeout=TimeSpan.FromHours(1);
				CMyHttpClientOperationRequest					Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

				CMyHttpClient.ExecuteMessage(Request);
			}

			// !!! Pocka sa kym neskonci PASSWORD LOCKOUT.
			Thread.Sleep(15000);

			{
				string											UserName="MyUser1";
				string											PhoneNumber="12345678";
				string											Password="zy3pQjPDJB0yL3J&";
				CMyUserModel									RawContent=new CMyUserModel(UserName,PhoneNumber,Password);

				string											MessageID=CommandID;
				EMyHttpClientHttpMethod							Method=EMyHttpClientHttpMethod.E_POST;
				string											URL=$"{BASE_ADDRESS}PasswordPolicy/Login";
				CMyHttpClientHeaders							Headers=null;
				CMyHttpClientContent							Content=CMyHttpClientContent.CreateContentJsonObject(RawContent);
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

			CommandsCollection.Add(new CMenuCommand("1","REGISTER PASSWORD OK",new EMenuCommandParameterType[0],ExecuteCommandRegisterPasswordOK));
			CommandsCollection.Add(new CMenuCommand("2","REGISTER PASSWORD WRONG",new EMenuCommandParameterType[0],ExecuteCommandRegisterPasswordWrong));
			CommandsCollection.Add(new CMenuCommand("3","LOGIN OK",new EMenuCommandParameterType[0],ExecuteCommandLoginOK));
			CommandsCollection.Add(new CMenuCommand("4","LOGIN WITH LOCKOUT",new EMenuCommandParameterType[0],ExecuteCommandLoginWithLockout));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------