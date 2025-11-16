using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace Constants
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CConstants
	{
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							SERVICE_BUS_NAMESPACE_NAME="MyServiceBusNamespaceTA76";
		public static readonly string							SERVICE_BUS_QUEUE_NAME="MyQueueTA76";
		public static readonly string							SERVICE_BUS_TOPIC_NAME="MyTopicTA76";
		public static readonly string							SERVICE_BUS_SUBSCRIPTION_NAME="MySubscriptionTA76";
		public static readonly string							SERVICE_BUS_SUBSCRIPTION_FILTER_1_NAME="MySubscriptionTA76Filter1";
		public static readonly string							SERVICE_BUS_SUBSCRIPTION_FILTER_2_NAME="MySubscriptionTA76Filter2";
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE=$"{SERVICE_BUS_NAMESPACE_NAME}.servicebus.windows.net";
		public static readonly string							SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE_URL=$"https://{SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE}";
		public static readonly string							SERVICE_BUS_FULLY_QUALIFIED_QUEUE_URL=$"https://{SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE}/{SERVICE_BUS_QUEUE_NAME}";
		public static readonly string							SERVICE_BUS_FULLY_QUALIFIED_TOPIC_URL=$"https://{SERVICE_BUS_FULLY_QUALIFIED_NAMESPACE}/{SERVICE_BUS_TOPIC_NAME}";
//----------------------------------------------------------------------------------------------------------------------
		// !!! CONNECTION STRING sa ziskava pomocou COMMAND [az servicebus namespace authorization-rule keys list --authorization-rule-name RootManageSharedAccessKey --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11].
		public static readonly string							SERVICE_BUS_NAMESPACE_CONNECTION_STRING="Endpoint=sb://myservicebusnamespaceta76.servicebus.windows.net/;SharedAccessKeyName=RootManageSharedAccessKey;SharedAccessKey=mN/+pbAOUDEGzoJu5UFLvt8VmDSSnBkDh+ASbDWoyZY=";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus namespace authorization-rule create --name MyBusNamespacePublisherRule --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Send].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_NAME_PUBLISHER="MyBusNamespacePublisherRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus namespace authorization-rule keys list --name MyBusNamespacePublisherRule --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_KEY_PUBLISHER="MjsccGjCx2XlTX8uX/C7nkSYKM4Uv3vIO+ASbDUpgJ0=";
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus namespace authorization-rule create --name MyBusNamespaceSubscriberRule --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Listen].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_NAME_SUBSCRIBER="MyBusNamespaceSubscriberRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus namespace authorization-rule keys list --name MyBusNamespaceSubscriberRule --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_NAMESPACE_KEY_SUBSCRIBER="7oKRBhOqJyCipQdnLQQx4pomkN93nHKAV+ASbBmsJZM=";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus queue authorization-rule create --name MyBusQueuePublisherRule --queue-name MyQueueTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Send].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_QUEUE_NAME_PUBLISHER="MyBusQueuePublisherRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus queue authorization-rule keys list --name MyBusQueuePublisherRule --queue-name MyQueueTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_QUEUE_KEY_PUBLISHER="8t0PuDXk72BzURdNvRlkXn210sQvFdG8S+ASbD/1WKk=";
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus queue authorization-rule create --name MyBusQueueSubscriberRule --queue-name MyQueueTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Listen].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_QUEUE_NAME_SUBSCRIBER="MyBusQueueSubscriberRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus queue authorization-rule keys list --name MyBusQueueSubscriberRule --queue-name MyQueueTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_QUEUE_KEY_SUBSCRIBER="YUjQjfXVqDUTL9RHopQssRJKcT8vaOitG+ASbJez268=";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus topic authorization-rule create --name MyBusTopicPublisherRule --topic-name MyTopicTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Send].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_NAME_PUBLISHER="MyBusTopicPublisherRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus topic authorization-rule keys list --name MyBusTopicPublisherRule --topic-name MyTopicTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_KEY_PUBLISHER="08x3k1Xvir3xAfR2hfMBdS9QXGLUoh+8Z+ASbAy/loE=";
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az servicebus topic authorization-rule create --name MyBusTopicSubscriberRule --topic-name MyTopicTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11 --rights Listen].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_NAME_SUBSCRIBER="MyBusTopicSubscriberRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az servicebus topic authorization-rule keys list --name MyBusTopicSubscriberRule --topic-name MyTopicTA76 --namespace-name MyServiceBusNamespaceTA76 --resource-group Chapter11] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_SERVICE_BUS_TOPIC_KEY_SUBSCRIBER="rAGb5LO9Hwo7GoMq6G9uro5n5m7cDrPMA+ASbAc3LhY=";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							TENANT_ID="fb51fbc4-63c4-41a5-8b6a-6f6e1434b7dd";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa ziskava z PROPERTY [appId] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_ID_PUBLISHER="acfb710d-a804-4a1e-8229-7eccde6c6908";
		// !!! VALUE sa ziskava z PROPERTY [password] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_SECRET_PUBLISHER="~oK8Q~jE4dDSe_6R0Ld52pyUekA3wT20pPfjkc9U";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa ziskava z PROPERTY [appId] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_ID_SUBSCRIBER="982cd04e-a075-4b4d-804e-8ac1602a3f1c";
		// !!! VALUE sa ziskava z PROPERTY [password] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_SECRET_SUBSCRIBER="Q7J8Q~RsJf1LjHE4or0BezN6dtwupbU5hGML~dAy";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							MESSAGE_FILTER_PROPERTY_NAME_1="MyProperty1";
		public static readonly string							MESSAGE_FILTER_PROPERTY_NAME_2="MyProperty2";
		public static readonly string							MESSAGE_FILTER_PROPERTY_NAME_3="MyTextProperty";
		public static readonly string							MESSAGE_FILTER_PROPERTY_VALUE_3="ABC";
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------