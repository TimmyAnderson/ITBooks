using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace Client
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuUserAssignedManagedIdentityAzure : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		// !!!!! Pre DOCKER sa pouziva HTTP, pretoze inak by bolo treba registrovat CERTIFICATE.
		private const string									BASE_ADDRESS="https://keyvaultuserassignedmanagedidentity.azurewebsites.net/";
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuUserAssignedManagedIdentityAzure()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandKeyVault(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandKeyVaultPost(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_POST;
			string												URL=$"{BASE_ADDRESS}KeyVault";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=CMyHttpClientContent.CreateContentJsonObject("MY TEXT");
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSecretDefaultCredentials(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetSecretDefaultCredentials";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity1(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity1";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity2(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity2";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSecretManagedIdentityCredentialsObjectID(string CommandID, object[] Parameters)
		{
			string												ObjectID=((string) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetSecretManagedIdentityCredentialsObjectID?ObjectID={ObjectID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSecretManagedIdentityCredentialsClientID(string CommandID, object[] Parameters)
		{
			string												ClientID=((string) Parameters[0]);

			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetSecretManagedIdentityCredentialsClientID?ClientID={ClientID}";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetKeyVaultReference(string CommandID, object[] Parameters)
		{
			string												MessageID=CommandID;
			EMyHttpClientHttpMethod								Method=EMyHttpClientHttpMethod.E_GET;
			string												URL=$"{BASE_ADDRESS}KeyVault/GetKeyVaultReference";
			CMyHttpClientHeaders								Headers=null;
			CMyHttpClientContent								Content=null;
			TimeSpan											Timeout=TimeSpan.FromHours(1);
			CMyHttpClientOperationRequest						Request=new CMyHttpClientOperationRequest(MessageID,Method,URL,Headers,Content,Timeout);

			CMyHttpClient.ExecuteMessage(Request);
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","TEST CONNECTION",new EMenuCommandParameterType[0],ExecuteCommandKeyVault));
			CommandsCollection.Add(new CMenuCommand("2","TEST CONNECTION POST",new EMenuCommandParameterType[0],ExecuteCommandKeyVaultPost));
			CommandsCollection.Add(new CMenuCommand("3","GET SECRET DEFAULT CREDENTIALS",new EMenuCommandParameterType[0],ExecuteCommandGetSecretDefaultCredentials));
			CommandsCollection.Add(new CMenuCommand("4","GET SECRET SYSTEM MANAGED IDENTITY CREDENTIALS 1",new EMenuCommandParameterType[0],ExecuteCommandGetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity1));
			CommandsCollection.Add(new CMenuCommand("5","GET SECRET SYSTEM MANAGED IDENTITY CREDENTIALS 2",new EMenuCommandParameterType[0],ExecuteCommandGetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity2));
			CommandsCollection.Add(new CMenuCommand("6","GET SECRET MANAGED IDENTITY CREDENTIALS OBJECT ID",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandGetSecretManagedIdentityCredentialsObjectID));
			CommandsCollection.Add(new CMenuCommand("7","GET SECRET MANAGED IDENTITY CREDENTIALS CLIENT ID",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandGetSecretManagedIdentityCredentialsClientID));
			CommandsCollection.Add(new CMenuCommand("8","GET KEY VAULT REFERENCE",new EMenuCommandParameterType[0],ExecuteCommandGetKeyVaultReference));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------