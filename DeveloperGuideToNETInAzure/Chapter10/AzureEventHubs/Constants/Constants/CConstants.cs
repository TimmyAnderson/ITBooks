using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace Constants.Constants
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CConstants
	{
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							EVENT_HUB_NAMESPACE="mynamespaceta76";
		public static readonly string							EVENT_HUB_NAME="MyHubTA76";
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							EVENT_HUB_FULLY_QUALIFIED_NAMESPACE=$"{EVENT_HUB_NAMESPACE}.servicebus.windows.net";
		public static readonly string							EVENT_HUB_FULLY_QUALIFIED_NAMESPACE_URL=$"https://{EVENT_HUB_FULLY_QUALIFIED_NAMESPACE}";
		public static readonly string							EVENT_HUB_FULLY_QUALIFIED_HUB_URL=$"https://{EVENT_HUB_FULLY_QUALIFIED_NAMESPACE}/{EVENT_HUB_NAME}";
		// !!! CONNECTION STRING sa ziskava pomocou COMMAND [az eventhubs namespace authorization-rule keys list --namespace-name MyNamespaceTA76 --resource-group Chapter10 --name RootManageSharedAccessKey].
		public static readonly string							EVENT_HUBS_CONNECTION_STRING="Endpoint=sb://mynamespaceta76.servicebus.windows.net/;SharedAccessKeyName=RootManageSharedAccessKey;SharedAccessKey=Zrbj/FxEA7WBrIwH3znXJ2yb4M3uYr7ew+AEhP7esiM=";
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACCOUNT KEY sa ziskava pomocou COMMAND [az storage account keys list --account-name mystorageta --resource-group Chapter10].
		public static readonly string							BLOB_STORAGE_ACCOUNT_KEY="6rhX9z9JF/v41bNIMTQtBJKRU4L3nxu4jfeFlrusPXw/aHVgXvx5EeD01SkX/u/AY4HcoXTP4f+r+AStMHBUxg==";
		public static readonly string							BLOB_STORAGE_CONNECTION_STRING=$"DefaultEndpointsProtocol=https;AccountName=mystorageta;AccountKey={BLOB_STORAGE_ACCOUNT_KEY}";
		public static readonly string							BLOB_CONTAINER_NAME="myblobcontainer";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az eventhubs namespace authorization-rule create --name MyNamespacePublisherRule --namespace-name MyNamespaceTA76 --resource-group Chapter10 --rights Send].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_NAME_PRODUCER="MyNamespacePublisherRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az eventhubs namespace authorization-rule keys list --name MyNamespacePublisherRule --namespace-name MyNamespaceTA76 --resource-group Chapter10] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_KEY_PRODUCER="ICFXzeM9vxCXJUXXFTmu4UBCOoh6LWmRk+AEhJI9yOM=";
//----------------------------------------------------------------------------------------------------------------------
		// !!! RULE sa vytvara pomocou COMMAND [az eventhubs namespace authorization-rule create --name MyNamespaceConsumerRule --namespace-name MyNamespaceTA76 --resource-group Chapter10 --rights Listen].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_NAME_CONSUMER="MyNamespaceConsumerRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az eventhubs namespace authorization-rule keys list --name MyNamespaceConsumerRule --namespace-name MyNamespaceTA76 --resource-group Chapter10] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_NAMESPACE_KEY_CONSUMER="AKKVUoS5AYFk9Ml/lt4p/oiTzkuTh3N03+AEhDORY4w=";
//----------------------------------------------------------------------------------------------------------------------
		// RULE sa vytvara pomocou COMMAND [az eventhubs eventhub authorization-rule create --name MyHubPublisherRule --eventhub-name MyHubTA76 --namespace-name MyNamespaceTA76 --resource-group Chapter10 --rights Send].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_HUB_NAME_PRODUCER="MyHubPublisherRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az eventhubs eventhub authorization-rule keys list --name MyHubPublisherRule --eventhub-name MyHubTA76 --namespace-name MyNamespaceTA76 --resource-group Chapter10] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_HUB_KEY_PRODUCER="2GGxMYPJIo+sogiIS4B5b/coGnS+w1CLn+AEhLGFX/o=";
//----------------------------------------------------------------------------------------------------------------------
		// RULE sa vytvara pomocou COMMAND [az eventhubs eventhub authorization-rule create --name MyHubConsumerRule --eventhub-name MyHubTA76 --namespace-name MyNamespaceTA76 --resource-group Chapter10 --rights Listen].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_HUB_NAME_CONSUMER="MyHubConsumerRule";
		// !!! VALUE sa ziskava pomocou COMMAND [az eventhubs eventhub authorization-rule keys list --name MyHubConsumerRule --eventhub-name MyHubTA76 --namespace-name MyNamespaceTA76 --resource-group Chapter10] z PROPERTY [primaryKey].
		public static readonly string							SAS_AUTHORIZATION_RULE_EVENT_HUBS_HUB_KEY_CONSUMER="AKKVUoS5AYFk9Ml/lt4p/oiTzkuTh3N03+AEhDORY4w=";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public static readonly string							TENANT_ID="fb51fbc4-63c4-41a5-8b6a-6f6e1434b7dd";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa ziskava z PROPERTY [appId] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_ID_PRODUCER="5dd09559-5d06-4c9e-9ba2-4af439a247e7";
		// !!! VALUE sa ziskava z PROPERTY [password] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_SECRET_PRODUCER="0d38Q~oiKLH6goyQBt2gu1eIf~dWL2.dIu2b5bQ8";
//----------------------------------------------------------------------------------------------------------------------
		// !!! VALUE sa ziskava z PROPERTY [appId] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_ID_CONSUMER="01293af8-ccbb-46fd-bdd2-f158360de86c";
		// !!! VALUE sa ziskava z PROPERTY [password] volanim COMMAND [az ad app credential reset].
		public static readonly string							CLIENT_CREDENTIALS_CLIENT_SECRET_CONSUMER="m6w8Q~tCL0zYCdAIZKbDTB2sUCddeR.6LYlCQblP";
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------