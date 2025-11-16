using System;
//----------------------------------------------------------------------------------------------------------------------
namespace ServiceBusPublisher
{
//----------------------------------------------------------------------------------------------------------------------
	public class Program
	{
//----------------------------------------------------------------------------------------------------------------------
		static void Main(string[] args)
		{
			//CMenuMessagePublisherQueue						Menu=new CMenuMessagePublisherQueue();
			//CMenuMessagePublisherTopic						Menu=new CMenuMessagePublisherTopic();

			//CMenuMessagePublisherQueueSaSCredentialsNamespace	Menu=new CMenuMessagePublisherQueueSaSCredentialsNamespace();
			//CMenuMessagePublisherQueueSaSCredentialsQueue		Menu=new CMenuMessagePublisherQueueSaSCredentialsQueue();
			//CMenuMessagePublisherTopicSaSCredentialsTopic		Menu=new CMenuMessagePublisherTopicSaSCredentialsTopic();
			//CMenuMessagePublisherQueueClientCredentials		Menu=new CMenuMessagePublisherQueueClientCredentials();

			CMenuMessagePublisherRetries						Menu=new CMenuMessagePublisherRetries();

			Menu.Execute();
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------