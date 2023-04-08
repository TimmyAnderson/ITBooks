using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace IncludeExceptionDetailInFaultsHost
{
//-------------------------------------------------------------------------------------------------------
	public class CFaultTestService : IFaultTestService
	{
//-------------------------------------------------------------------------------------------------------
		public void Dummy()
		{
			Console.WriteLine("Dummy() !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowNonFaultException()
		{
			Console.WriteLine("ThrowNonFaultException() !");

			throw(new InvalidProgramException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowFaultException()
		{
			Console.WriteLine("ThrowFaultException() !");

			throw(new FaultException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------