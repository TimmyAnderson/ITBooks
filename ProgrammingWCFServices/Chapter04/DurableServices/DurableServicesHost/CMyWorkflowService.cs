using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
//-------------------------------------------------------------------------------------------------------
namespace DurableServicesHost
{
//-------------------------------------------------------------------------------------------------------
	// !!! Service class MUSI BYT SERIALIZABLE.
	[DataContract]
	// Service class musim oznacit atributom [DurableService].
	[DurableService]
	public class CMyWorkflowService : IMyWorkflowService, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		// Ulozi sa do PS ak je oznacena ako [DataMember].
		[DataMember]
		private string							MFirstName;
		// Ulozi sa do PS ak je oznacena ako [DataMember].
		[DataMember]
		private string							MLastName;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CMyWorkflowService()
		{
			Console.WriteLine("---------------------------------------------------------");
			Console.WriteLine("SERVICE INSTANCE CREATED !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void PrintState(string MethodName)
		{
			string						InstanceId="EMPTY";

			// Sposob ako ziskat CELY Context - nielen InstanceId.
			if (OperationContext.Current.IncomingMessageProperties.ContainsKey(ContextMessageProperty.Name)==true)
			{
				ContextMessageProperty		ContextProperty=OperationContext.Current.IncomingMessageProperties[ContextMessageProperty.Name] as ContextMessageProperty;
				IDictionary<string,string>	Context=ContextProperty.Context;

				InstanceId=Context["instanceId"];
			}

			Console.WriteLine(string.Format("{0}() - FirstName: {1}, LastName: {2}, InstanceId: {3}, ObjectHash: {4}, AltInstanceID: {5} !",MethodName,MFirstName,MLastName,DurableOperationContext.InstanceId,this.GetHashCode(),InstanceId));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// Jedine tato operacia zacina novy WF.
		[DurableOperation(CanCreateInstance=true,CompletesInstance=false)]
		public void SetFirstName(string FirstName)
		{
			MFirstName=FirstName;

			PrintState("SetFirstName");
		}
//-------------------------------------------------------------------------------------------------------
		[DurableOperation(CanCreateInstance=false,CompletesInstance=false)]
		public void SetLastName(string LastName)
		{
			MLastName=LastName;

			PrintState("SetLastName");
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda ukonci WF pomocou atributu.
		[DurableOperation(CanCreateInstance=false,CompletesInstance=true)]
		public void PrintFullNameAndFinishWFByAttribute()
		{
			PrintState("PrintFullNameAndFinishWFByAttribute");
		}
//-------------------------------------------------------------------------------------------------------
		// Metoda ukonci WF pomocou kodu.
		[DurableOperation(CanCreateInstance=false,CompletesInstance=false)]
		public void PrintFullNameAndFinishWFByCode()
		{
			PrintState("PrintFullNameAndFinishWFByCode");

			// Ukoncim WF.
			DurableOperationContext.CompleteInstance();
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("SERVICE INSTANCE DESTROYED !");
			Console.WriteLine("---------------------------------------------------------");
			Console.WriteLine("");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------