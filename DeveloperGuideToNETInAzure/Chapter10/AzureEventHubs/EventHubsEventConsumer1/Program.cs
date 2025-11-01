using System;
//----------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventConsumer1
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="1";

			CMenuEventConsumer									Menu=new CMenuEventConsumer();
			//CMenuEventConsumerSasCredentialEventHubsNamespace	Menu=new CMenuEventConsumerSasCredentialEventHubsNamespace();
			//CMenuEventConsumerSasCredentialEventHubsHub		Menu=new CMenuEventConsumerSasCredentialEventHubsHub();
			//CMenuEventConsumerClientSecretCredential			Menu=new CMenuEventConsumerClientSecretCredential();

			Menu.Execute();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------