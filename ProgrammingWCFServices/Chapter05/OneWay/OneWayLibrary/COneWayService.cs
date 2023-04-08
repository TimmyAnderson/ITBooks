using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace OneWayLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class COneWayService : IOneWayContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		public COneWayService()
		{
			Console.WriteLine("COneWayService CONSTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void MethodWithoutException()
		{
			Console.WriteLine("COneWayService.MethodWithoutException() called STARTED !");
			Thread.Sleep(10*1000);
			Console.WriteLine("COneWayService.MethodWithoutException() called FINISHED !");
		}
//-------------------------------------------------------------------------------------------------------
		public void MethodWithException()
		{
			Console.WriteLine("COneWayService.MethodWithException() called !");
			throw(new Exception("EXCEPTION FORM Service"));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("COneWayService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------