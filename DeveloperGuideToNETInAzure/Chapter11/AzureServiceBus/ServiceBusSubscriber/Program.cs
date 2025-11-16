using System;
//----------------------------------------------------------------------------------------------------------------------
namespace ServiceBusSubscriber
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuMessageSubscriberProcessorQueue				Menu=new CMenuMessageSubscriberProcessorQueue();
			//CMenuMessageSubscriberReceiverQueue				Menu=new CMenuMessageSubscriberReceiverQueue();

			//CMenuMessageSubscriberProcessorSubscription		Menu=new CMenuMessageSubscriberProcessorSubscription();
			//CMenuMessageSubscriberReceiverSubscription		Menu=new CMenuMessageSubscriberReceiverSubscription();

			//CMenuMessageSubscriberReceiverQueueSaSCredentialsNamespace	Menu=new CMenuMessageSubscriberReceiverQueueSaSCredentialsNamespace();
			//CMenuMessageSubscriberReceiverQueueSaSCredentialsQueue	Menu=new CMenuMessageSubscriberReceiverQueueSaSCredentialsQueue();
			//CMenuMessageSubscriberReceiverSubscriptionSaSCredentialsTopic	Menu=new CMenuMessageSubscriberReceiverSubscriptionSaSCredentialsTopic();
			//CMenuMessageSubscriberReceiverQueueClientCredentials	Menu=new CMenuMessageSubscriberReceiverQueueClientCredentials();

			//CMenuMessageSubscriberReceiverSubscriptionDeadLetterQueue	Menu=new CMenuMessageSubscriberReceiverSubscriptionDeadLetterQueue();

			CMenuMessageSubscriberReceiverRetries				Menu=new CMenuMessageSubscriberReceiverRetries();

			Menu.Execute();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------