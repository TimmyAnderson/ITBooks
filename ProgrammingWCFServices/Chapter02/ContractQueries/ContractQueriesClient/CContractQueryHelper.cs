using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ContractQueriesClient
{
//-------------------------------------------------------------------------------------------------------
	class CContractQueryHelper
	{
//-------------------------------------------------------------------------------------------------------
		private ServiceEndpointCollection						MServiceEndpointCollection;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ReadServiceEndpointCollection(string MEXAddress, BindingElement Element)
		{
			try
			{
				CustomBinding			Binding=new CustomBinding(Element);
				MetadataExchangeClient	MEXClient=new MetadataExchangeClient(Binding);
				MetadataSet				MetaData=MEXClient.GetMetadata(new EndpointAddress(MEXAddress));
				MetadataImporter		Importer=new WsdlImporter(MetaData);
	     
				MServiceEndpointCollection=Importer.ImportAllEndpoints();
			}
			catch(Exception E)
			{
				Console.WriteLine(String.Format("Exception: {0} !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void WriteServiceEndpointCollectionToConsole()
		{
			if (MServiceEndpointCollection!=null)
			{
				foreach(ServiceEndpoint SE in MServiceEndpointCollection)
				{
					Console.WriteLine(String.Format("Contract.Name: {0} !",SE.Contract.Name.ToString()));
					Console.WriteLine(String.Format("Contract.Namespace: {0} !",SE.Contract.Namespace.ToString()));
					Console.WriteLine(String.Format("Address: {0} !",SE.Address.ToString()));
					Console.WriteLine(String.Format("Binding: {0} !",SE.Binding.ToString()));

					foreach(OperationDescription OD in SE.Contract.Operations)
					{
						Console.WriteLine(String.Format("\tOperation.Name: {0} !",OD.Name.ToString()));
					}

					Console.WriteLine("");
				}
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------