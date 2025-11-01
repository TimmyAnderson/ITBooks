//----------------------------------------------------------------------------------------------------------------------
namespace EventHubsEventPublisher
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuEventProducer								Menu=new CMenuEventProducer();
			//CMenuEventBufferedProducer						Menu=new CMenuEventBufferedProducer();
			CMenuEventProducerRetries							Menu=new CMenuEventProducerRetries();
			//CMenuEventProducerSasCredentialEventHubsNamespace	Menu=new CMenuEventProducerSasCredentialEventHubsNamespace();
			//CMenuEventProducerSasCredentialEventHubsHub		Menu=new CMenuEventProducerSasCredentialEventHubsHub();
			//CMenuEventProducerClientSecretCredential			Menu=new CMenuEventProducerClientSecretCredential();

			Menu.Execute();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------