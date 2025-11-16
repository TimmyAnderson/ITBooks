using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Azure;
using Azure.Messaging.ServiceBus;
using Azure.Messaging.ServiceBus.Administration;
using Constants;
using MySharedLibrary;
//--------------------------------------------------------------------------------------------------------------------------------
namespace ServiceBusManagement
{
//--------------------------------------------------------------------------------------------------------------------------------
	public sealed class CMenuMessageManagement : CMenu
	{
//--------------------------------------------------------------------------------------------------------------------------------
		public CMenuMessageManagement()
			: base(new CMenuCommand("q","QUIT",new EMenuCommandParameterType[0],null))
		{
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetNamespaceProperties(string CommandID, object[] Parameters)
		{
			try
			{
				ServiceBusAdministrationClient					AdministrationClient=new ServiceBusAdministrationClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING);

				Response<NamespaceProperties>					Response=AdministrationClient.GetNamespacePropertiesAsync().Result;
				NamespaceProperties								Properties=Response.Value;

				string											Name=Properties.Name ?? "";
				string											Alias=Properties.Alias ?? "";

				Console.WriteLine($"NAMESPACE - NAME [{Name}] ALIAS [{Alias}].");
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetQueuesProperties(string CommandID, object[] Parameters)
		{
			try
			{
				ServiceBusAdministrationClient					AdministrationClient=new ServiceBusAdministrationClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING);

				QueueProperties[]								AllProperties=AdministrationClient.GetQueuesAsync().ToBlockingEnumerable().ToArray();

				foreach(QueueProperties Properties in AllProperties)
				{
					string										Name=Properties.Name ?? "";
					string										Status=Properties.Status.ToString() ?? "";

					Console.WriteLine($"QUEUE - NAME [{Name}] STATUS [{Status}].");
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetTopicsProperties(string CommandID, object[] Parameters)
		{
			try
			{
				ServiceBusAdministrationClient					AdministrationClient=new ServiceBusAdministrationClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING);

				TopicProperties[]								AllProperties=AdministrationClient.GetTopicsAsync().ToBlockingEnumerable().ToArray();

				foreach(TopicProperties Properties in AllProperties)
				{
					string										Name=Properties.Name ?? "";
					string										Status=Properties.Status.ToString() ?? "";
				
					Console.WriteLine($"TOPIC - NAME [{Name}] STATUS [{Status}].");
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
		private void ExecuteCommandGetSubscriptionsProperties(string CommandID, object[] Parameters)
		{
			string												TopicInputName=((string) Parameters[0]);

			try
			{
				ServiceBusAdministrationClient					AdministrationClient=new ServiceBusAdministrationClient(CConstants.SERVICE_BUS_NAMESPACE_CONNECTION_STRING);

				SubscriptionProperties[]						AllProperties=AdministrationClient.GetSubscriptionsAsync(TopicInputName).ToBlockingEnumerable().ToArray();

				foreach(SubscriptionProperties Properties in AllProperties)
				{
					string										TopicName=Properties.TopicName ?? "";
					string										SubscriptionName=Properties.SubscriptionName ?? "";
					string										Status=Properties.Status.ToString() ?? "";
				
					Console.WriteLine($"SUBSCRIPTION - TOPIC NAME [{TopicName}] SUBSCRIPTION NAME [{SubscriptionName}] STATUS [{Status}].");
				}
			}
			catch(ServiceBusException E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}]. ENTITY PATH [{E.EntityPath}] REASON [{E.Reason}].");
			}
			catch(Exception E)
			{
				Console.WriteLine($"EXCEPTION [{E.Message}].");
			}
		}
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------
		protected override CMenuCommand[] GetCommands()
		{
			List<CMenuCommand>									CommandsCollection=new List<CMenuCommand>();

			CommandsCollection.Add(new CMenuCommand("1","GET NAMESPACE PROPERTIES",new EMenuCommandParameterType[0],ExecuteCommandGetNamespaceProperties));
			CommandsCollection.Add(new CMenuCommand("2","GET QUEUES",new EMenuCommandParameterType[0],ExecuteCommandGetQueuesProperties));
			CommandsCollection.Add(new CMenuCommand("3","GET TOPICS",new EMenuCommandParameterType[0],ExecuteCommandGetTopicsProperties));
			CommandsCollection.Add(new CMenuCommand("4","GET SUBSCRIPTIONS",new EMenuCommandParameterType[]{EMenuCommandParameterType.E_STRING},ExecuteCommandGetSubscriptionsProperties));

			CMenuCommand[]										Commands=CommandsCollection.ToArray();

			return(Commands);
		}
//--------------------------------------------------------------------------------------------------------------------------------
	}
//--------------------------------------------------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------------------------------------