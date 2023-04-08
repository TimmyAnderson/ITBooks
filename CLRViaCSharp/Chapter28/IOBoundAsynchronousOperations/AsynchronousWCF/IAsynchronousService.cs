using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousWCF
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IAsynchronousService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		string SlowOperation(string Parameter);
		[OperationContract]
		Task<string> AsynchronousSlowOperation(string Parameter);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------