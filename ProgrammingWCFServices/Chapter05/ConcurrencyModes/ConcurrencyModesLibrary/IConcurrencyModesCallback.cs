using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ConcurrencyModesLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceContract]
	public interface IConcurrencyModesCallback
	{
//-------------------------------------------------------------------------------------------------------
		[OperationContract]
		void OnCallback(string Message);
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------