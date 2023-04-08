using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
//-------------------------------------------------------------------------------------------------------
namespace DCDelegatesSharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public class CTestService : ITestService
	{
//-------------------------------------------------------------------------------------------------------
		private static void StaticHandler(string SomeParam)
		{
			Console.WriteLine(string.Format("StaticHandler(): [{0}] !",SomeParam));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void InstanceHandler(string SomeParam)
		{
			Console.WriteLine(string.Format("InstanceHandler(): [{0}] !",SomeParam));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void ConnectionTest()
		{
			Console.WriteLine("TEST SUCCEEDED !");
		}
//-------------------------------------------------------------------------------------------------------
		public DMyDelegate ReceiveEmptyDelegate()
		{
			DMyDelegate			Delegate=null;

			Console.WriteLine("SERVICE CALLED !");

			return(Delegate);
		}
//-------------------------------------------------------------------------------------------------------
		public DMyDelegate ReceiveDelegateToStaticMethod()
		{
			DMyDelegate			Delegate=new DMyDelegate(StaticHandler);

			Console.WriteLine("SERVICE CALLED !");

			return(Delegate);
		}
//-------------------------------------------------------------------------------------------------------
		public DMyDelegate ReceiveDelegateToInstanceMethod()
		{
			DMyDelegate			Delegate=new DMyDelegate(InstanceHandler);

			Console.WriteLine("SERVICE CALLED !");

			return(Delegate);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------