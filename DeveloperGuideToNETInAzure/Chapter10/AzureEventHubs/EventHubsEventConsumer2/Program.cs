using System;
//----------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventConsumer2
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="2";

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