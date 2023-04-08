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
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession,IncludeExceptionDetailInFaults=true)]
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CSimpleFaultsPerSessionService : ISimpleFaultsPerSessionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CSimpleFaultsPerSessionService()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowSimpleException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService.ThrowSimpleException() called !");

			throw(new CMySimpleFaultException("per-session SIMPLE exception"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService.ThrowCMyFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("per-session FAULT exception");

			throw(new CMyFaultException(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCMyFaultException()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService.ThrowFaultException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("per-session FAULT exception");

			throw(new CMyFaultException(FaultDetails));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CSimpleFaultsPerSessionService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------