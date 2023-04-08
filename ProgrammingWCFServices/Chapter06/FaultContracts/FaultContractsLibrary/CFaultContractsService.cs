using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
// 1. Ak vraciam klasicku ne FaultException (InvalidOperationException) ALE NIE CEZ FaultException BEZ OHLADU, ZE JE InvalidOperationException je ako Fault Contract potom sa vrati do klienta ako FaultException a Proxy je MRTVE.
// 2. Ak vraciam FaultException potom sa vrati do klienta ako FaultException A PROXY ZIJE.
// 3. Ak vraciam FaultException<InvalidOperationException> potom sa vrati do klienta ako FaultException<InvalidOperationException> A PROXY ZIJE.
// 4. Ak vraciam FaultException<ExceptionDetail> potom sa vrati do klienta ako FaultException<ExceptionDetail> A PROXY ZIJE.
// 5. Ak vraciam FaultException<CFaultDetails> potom sa vrati do klienta ako FaultException<CFaultDetails> A PROXY ZIJE.
// !!!!! 6. Inak povedane FaultException sluzi na PRENOS EXCEPTION cez FaultContract. Ina Exception ZNICI PROXY, kedze nie je povazovana za sucast FaultContract.
//-------------------------------------------------------------------------------------------------------
namespace FaultContractsLibrary
{
//-------------------------------------------------------------------------------------------------------
	//[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,IncludeExceptionDetailInFaults=true)]
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CFaultContractsService : IFaultContractsContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CFaultContractsService()
		{
			Console.WriteLine("CFaultContractsService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CFaultContractsService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowCFaultDetailsException()
		{
			Console.WriteLine("CFaultContractsService.ThrowCFaultDetailsException() called !");

			CFaultDetails				FaultDetails=new CFaultDetails("SOME DETAILS");

			throw(new FaultException<CFaultDetails>(FaultDetails,new FaultReason("SOME REASON")));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowInvalidOperationException()
		{
			Console.WriteLine("CFaultContractsService.ThrowInvalidOperationException() called !");

			throw(new InvalidOperationException("SOME INVALID OPERATION"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowInvalidOperationAsFaultException()
		{
			Console.WriteLine("CFaultContractsService.ThrowInvalidOperationAsFaultException() called !");

			InvalidOperationException		IO=new InvalidOperationException("SOME INVALID OPERATION FAULT EXCEPTION");

			throw(new FaultException<InvalidOperationException>(IO));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("CFaultContractsService.ThrowFaultException() called !");

			throw(new FaultException("SOME FAULT"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowExceptionDetail()
		{
			Console.WriteLine("CFaultContractsService.ThrowExceptionDetail() called !");

			InvalidOperationException		IO=new InvalidOperationException("SOME INVALID OPERATION");
			ExceptionDetail					ED=new ExceptionDetail(IO);

			throw(new FaultException<ExceptionDetail>(ED));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CFaultContractsService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------