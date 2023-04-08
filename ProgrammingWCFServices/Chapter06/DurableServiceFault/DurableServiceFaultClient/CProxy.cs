using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using DurableServiceFaultHost;
//-------------------------------------------------------------------------------------------------------
namespace DurableServiceFaultClient
{
//-------------------------------------------------------------------------------------------------------
	public class CProxy : ClientBase<IMyWorkflowService>, IMyWorkflowService
	{
//-------------------------------------------------------------------------------------------------------
		// Tento konstruktor sa pouziva pri VYTVORENI NOVEHO WF.
		public CProxy()
		{
		}
//-------------------------------------------------------------------------------------------------------
		// Tento konstruktor sa pouziva pri PRIPOJENI SA NA BEZIACI WF.
		public CProxy(string ID)
		{
			// Skontrolujem ci Binding podporuje ContextBindingElement.
			BindingElementCollection		Elements=Endpoint.Binding.CreateBindingElements();
         
			if (Elements.Contains(typeof(ContextBindingElement))==false)
				throw(new InvalidOperationException("CONTEXT BINDING NOT USED !"));

			IContextManager					CM=InnerChannel.GetProperty<IContextManager>();
			Dictionary<string,string>		Context=new Dictionary<string,string>();

			// 'instanceId' je PRESNE DEFINOVANA KONSTANTA vo WCF.
			Context.Add("instanceId",ID);

			CM.SetContext(Context);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		internal string GetInstanceID()
		{
			BindingElementCollection		Elements=Endpoint.Binding.CreateBindingElements();
         
			if (Elements.Contains(typeof(ContextBindingElement))==false)
				throw(new InvalidOperationException("CONTEXT BINDING NOT USED !"));

			IContextManager					CM=InnerChannel.GetProperty<IContextManager>();
			IDictionary<string,string>		Context=CM.GetContext();
			string							InstanceID=Context["instanceId"];
			
			return(InstanceID);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SetFirstName(string FirstName)
		{
			Channel.SetFirstName(FirstName);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetLastName(string LastName)
		{
			Channel.SetLastName(LastName);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetLastNameButThrowException(string LastName)
		{
			Channel.SetLastNameButThrowException(LastName);
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintFullNameAndFinishWFByAttribute()
		{
			Channel.PrintFullNameAndFinishWFByAttribute();
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintFullNameAndFinishWFByCode()
		{
			Channel.PrintFullNameAndFinishWFByCode();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------