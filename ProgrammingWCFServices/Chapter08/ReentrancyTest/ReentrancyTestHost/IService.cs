using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ReentrancyTestHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract(SessionMode=SessionMode.Allowed,CallbackContract=typeof(ICallback))]
	public interface IService
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void SomeOperation(string Value);
		[OperationContract]
		void SomeOperationWithCallback(string Value);
		[OperationContract]
		void Dummy();
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------