using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Data;
using DCDataTableLibrary;
//-------------------------------------------------------------------------------------------------------
namespace DCDataTableManualClient
{
//-------------------------------------------------------------------------------------------------------
	public class CDCDataTableManualProxy : ClientBase<IDCDataTableContract>, IDCDataTableContract
	{
//-------------------------------------------------------------------------------------------------------
		public CDCDataTableManualProxy(Binding ProxyBinding, string EndpointAddress)
			: base(ProxyBinding, new EndpointAddress(EndpointAddress))
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public DataTable GetDataTable()
		{
 			return(Channel.GetDataTable());
		}
//-------------------------------------------------------------------------------------------------------
		public void SendDataTable(DataTable Table)
		{
 			Channel.SendDataTable(Table);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------