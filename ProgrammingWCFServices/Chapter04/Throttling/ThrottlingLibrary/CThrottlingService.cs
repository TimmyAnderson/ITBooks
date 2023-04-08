using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace ThrottlingLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CThrottlingService : IThrottlingContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static int										MCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CThrottlingService()
		{
			MCounter++;
			Console.WriteLine(string.Format("CThrottlingService CONSTRUCTOR called (Counter: {0}) !",MCounter));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void StartInstance()
		{
			Console.WriteLine(string.Format("CThrottlingService.StartSession() called (Counter: {0}) !",MCounter));
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.AfterCall)]
		public void DropInstance()
		{
			Console.WriteLine(string.Format("CThrottlingService.DropSession() called (Counter: {0}) !",MCounter));
		}
//-------------------------------------------------------------------------------------------------------
		public void SlowMethod(int Timeout)
		{
			Console.WriteLine(string.Format("CThrottlingService.DropSession() called (Counter: {0}) STARTED !",MCounter));
			Thread.Sleep(Timeout);
			Console.WriteLine(string.Format("CThrottlingService.DropSession() called (Counter: {0}) FINISHED !",MCounter));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			MCounter--;
			Console.WriteLine(string.Format("CThrottlingService DESTRUCTOR called (Counter: {0}) !",MCounter));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------