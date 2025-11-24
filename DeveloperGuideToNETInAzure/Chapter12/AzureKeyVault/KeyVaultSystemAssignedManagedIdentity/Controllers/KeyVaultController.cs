using System;
using System.Collections.Generic;
using System.Linq;
using Azure.Identity;
using Azure.Security.KeyVault.Secrets;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
//----------------------------------------------------------------------------------------------------------------------
namespace KeyVaultSystemAssignedManagedIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class KeyVaultController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private const string									KEY_VAULT_URI="https://mykeyvaultta76.vault.azure.net/";
		private const string									KEY_VAULT_SECRET_NAME="MySecretName";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private readonly IConfiguration							MConfiguration;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public KeyVaultController(IConfiguration Configuration)
		{
			MConfiguration=Configuration;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public string GetValue()
		{
			return("Hello WORLD - [SystemAssignedManagedIdentity] !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public string PostValue([FromBody] string Value)
		{
			return($"Hello [{Value}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetSecretDefaultCredentials")]
		public string GetSecretDefaultCredentials()
		{
			try
			{
				DefaultAzureCredential							Credential=new DefaultAzureCredential();
				Uri												KeyVaultUri=new Uri(KEY_VAULT_URI);
				SecretClient									Client=new SecretClient(KeyVaultUri,Credential);
				KeyVaultSecret									Secret=Client.GetSecret(KEY_VAULT_SECRET_NAME);
				string											SecretValue=Secret.Value;
				string											Result=$"SECRET [{SecretValue}].";

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"DEFAULT CREDENTIALS - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity1")]
		public string GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity1()
		{
			try
			{
				// !!!!! Pouzije sa SYSTEM ASSIGNED MANAGED IDENTITY daneho RESOURCE.
				ManagedIdentityCredential						Credential=new ManagedIdentityCredential();
				Uri												KeyVaultUri=new Uri(KEY_VAULT_URI);
				SecretClient									Client=new SecretClient(KeyVaultUri,Credential);
				KeyVaultSecret									Secret=Client.GetSecret(KEY_VAULT_SECRET_NAME);
				string											SecretValue=Secret.Value;
				string											Result=$"NO ID - SECRET [{SecretValue}].";

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"SYSTEM IDENTITY 1 - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity2")]
		public string GetSecretManagedIdentityCredentialsSystemAssignedManagedIdentity2()
		{
			try
			{
				ManagedIdentityId								ID=ManagedIdentityId.SystemAssigned;
				ManagedIdentityCredential						Credential=new ManagedIdentityCredential(ID);
				Uri												KeyVaultUri=new Uri(KEY_VAULT_URI);
				SecretClient									Client=new SecretClient(KeyVaultUri,Credential);
				KeyVaultSecret									Secret=Client.GetSecret(KEY_VAULT_SECRET_NAME);
				string											SecretValue=Secret.Value;
				string											Result=$"NO ID - SECRET [{SecretValue}].";

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"SYSTEM IDENTITY 2 - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetSecretManagedIdentityCredentialsObjectID")]
		public string GetSecretManagedIdentityCredentialsObjectID(string ObjectID)
		{
			try
			{
				ManagedIdentityId								ID=ManagedIdentityId.FromUserAssignedObjectId(ObjectID);
				ManagedIdentityCredential						Credential=new ManagedIdentityCredential(ID);
				Uri												KeyVaultUri=new Uri(KEY_VAULT_URI);
				SecretClient									Client=new SecretClient(KeyVaultUri,Credential);
				KeyVaultSecret									Secret=Client.GetSecret(KEY_VAULT_SECRET_NAME);
				string											SecretValue=Secret.Value;
				string											Result=$"OBJECT ID - SECRET [{SecretValue}].";
				
				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"OBJECT ID [{ObjectID}] - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetSecretManagedIdentityCredentialsClientID")]
		public string GetSecretManagedIdentityCredentialsClientID(string ClientID)
		{
			try
			{
				ManagedIdentityId								ID=ManagedIdentityId.FromUserAssignedClientId(ClientID);
				ManagedIdentityCredential						Credential=new ManagedIdentityCredential(ID);
				Uri												KeyVaultUri=new Uri(KEY_VAULT_URI);
				SecretClient									Client=new SecretClient(KeyVaultUri,Credential);
				KeyVaultSecret									Secret=Client.GetSecret(KEY_VAULT_SECRET_NAME);
				string											SecretValue=Secret.Value;
				string											Result=$"CLIENT ID - SECRET [{SecretValue}].";

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"CLIENT ID [{ClientID}] - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("GetKeyVaultReference")]
		public string GetKeyVaultReference()
		{
			try
			{
				string											SecretValue=MConfiguration["MySecretFromKeyVault"];
				string											Result=$"REFERENCE - SECRET [{SecretValue}].";

				return(Result);
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");

				string											Result=$"REFERENCE - EXCEPTION [{E.Message}].";

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------