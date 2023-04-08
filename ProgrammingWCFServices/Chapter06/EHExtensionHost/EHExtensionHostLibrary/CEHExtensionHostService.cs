using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace EHExtensionHostLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	// !!! Na service neaplikuem atribut, kedze ho instaluje autmaticky host.
	public class CEHExtensionHostService : IEHExtensionHostContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public CEHExtensionHostService()
		{
			Console.WriteLine("CEHExtensionHostService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void IsAlive()
		{
			Console.WriteLine("CEHExtensionHostService.IsAlive() called !");
		}
//-------------------------------------------------------------------------------------------------------
		public void ThrowException()
		{
			Console.WriteLine("CEHExtensionHostService.ThrowException() called !");

			InvalidOperationException		IOE=new InvalidOperationException("SOME INVALID OPERATION");

			throw(IOE);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CEHExtensionHostService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------