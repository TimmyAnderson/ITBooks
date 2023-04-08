using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ErrorHandlingExtensionsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	// Moj atribut - obsahuje IErrorHandler kod a je to vlastne moj Behavior.
	[CMyErrorHandlerBehavior()]
	public class CErrorHandlingExtensionsService : IErrorHandlingExtensionsContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CErrorHandlingExtensionsService()
		{
			Console.WriteLine("CErrorHandlingExtensionsService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CErrorHandlingExtensionsService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void CaughtException()
		{
			Console.WriteLine("CErrorHandlingExtensionsService.CaughtException() called 1 !");

			try
			{
				throw(new Exception("CaughtException"));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("Exception - CaughtException(): {0} !",E.Message));
			}

			Console.WriteLine("CErrorHandlingExtensionsService.CaughtException() called 2 !");
		}
//-------------------------------------------------------------------------------------------------------
		public void PromoteAllException()
		{
			Console.WriteLine("CErrorHandlingExtensionsService.PromoteAllException() called !");

			InvalidOperationException		IOE=new InvalidOperationException("SOME INVALID OPERATION");

			throw(IOE);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CErrorHandlingExtensionsService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------