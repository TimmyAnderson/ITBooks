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
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,IncludeExceptionDetailInFaults=true)]
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CSimpleFaultsPerCallService : ISimpleFaultsPerCallContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsPerCallService()
		{
			Console.WriteLine("CSimpleFaultsPerCallService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsPerCallService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsPerCallService.ThrowSimpleException() called !");

			throw(new CMySimpleFaultException("per-call SIMPLE exception"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerCallService.ThrowFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("per-call FAULT exception");

			throw(new FaultException<CFaultDetails>(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerCallService.ThrowCMyFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("per-call FAULT exception");

			throw(new CMyFaultException(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CSimpleFaultsPerCallService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------