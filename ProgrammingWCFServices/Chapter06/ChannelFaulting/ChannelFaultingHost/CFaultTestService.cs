using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ChannelFaultingHost
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
		public void NoFaultContractStandardException()
		{
			Console.WriteLine("NoFaultContractStandardException() !");

			throw(new InvalidProgramException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
		public void NoFaultContractFaultException()
		{
			Console.WriteLine("NoFaultContractFaultException() !");

			throw(new FaultException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
		public void NoFaultContractTypedFaultException()
		{
			Console.WriteLine("NoFaultContractTypedFaultException() !");

			InvalidProgramException		E=new InvalidProgramException("MY SERVICE BUG !!!");

			throw(new FaultException<InvalidProgramException>(E,"FAULT"));
		}
//-------------------------------------------------------------------------------------------------------
		public void WithFaultContractStandardException()
		{
			Console.WriteLine("WithFaultContractStandardException() !");

			throw(new InvalidProgramException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
		public void WithFaultContractFaultException()
		{
			Console.WriteLine("WithFaultContractFaultException() !");

			throw(new FaultException("MY SERVICE BUG !!!"));
		}
//-------------------------------------------------------------------------------------------------------
		public void WithFaultContractTypedFaultException()
		{
			Console.WriteLine("WithFaultContractTypedFaultException() !");

			InvalidProgramException		E=new InvalidProgramException("MY SERVICE BUG !!!");

			throw(new FaultException<InvalidProgramException>(E,"FAULT"));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------