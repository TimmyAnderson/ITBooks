using System;
//----------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventConsumer3
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			Console.Title="3";

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