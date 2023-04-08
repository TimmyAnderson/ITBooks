using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SimpleFaultsLibrary
{
//-------------------------------------------------------------------------------------------------------
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single,IncludeExceptionDetailInFaults=true)]
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single)]
	public class CSimpleFaultsSingletonService : ISimpleFaultsSingletonContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsSingletonService()
		{
			Console.WriteLine("CSimpleFaultsSingletonService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsSingletonService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsSingletonService.ThrowSimpleException() called !");

			throw(new CMySimpleFaultException("singleton SIMPLE exception"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsSingletonService.ThrowFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("singleton FAULT exception");

			throw(new CMyFaultException(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsSingletonService.ThrowCMyFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("singleton FAULT exception");

			throw(new CMyFaultException(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CSimpleFaultsSingletonService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------