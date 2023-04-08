using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.ServiceModel.Description;
using System.ServiceModel.Dispatcher;
using TransactionalDurableServicesHost;
//-------------------------------------------------------------------------------------------------------
namespace TransactionalDurableServicesClient
{
//-------------------------------------------------------------------------------------------------------
	public class CProxy : ClientBase<IMyService>, IMyService
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
		public void StartWorkflow(string SomePersistentValue)
		{
			Channel.StartWorkflow(SomePersistentValue);
		}
//-------------------------------------------------------------------------------------------------------
		public void DoTransaction(string SomePersistentValue, bool CommitTransaction)
		{
			Channel.DoTransaction(SomePersistentValue, CommitTransaction);
		}
//-------------------------------------------------------------------------------------------------------
		public void FinishWorkflow()
		{
			Channel.FinishWorkflow();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------