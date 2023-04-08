using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace ReentrancyTestHost
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Reentrant)]
	public class CService : IService
	{
//-------------------------------------------------------------------------------------------------------
		private int												MCounter=0;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SomeOperation(string Value)
		{
			MCounter++;

			Console.WriteLine(string.Format("BEGIN SomeOperation() - Counter: {0}, Value: {1} !",MCounter,Value));

			Thread.Sleep(5*1000);

			Console.WriteLine(string.Format("END SomeOperation() - Counter: {0}, Value: {1} !",MCounter,Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void SomeOperationWithCallback(string Value)
		{
			MCounter++;

			Console.WriteLine(string.Format("BEGIN SomeOperationWithCallback() - Counter: {0}, Value: {1} !",MCounter,Value));

			ICallback			Callback=OperationContext.Current.GetCallbackChannel<ICallback>();

			Callback.SomeCallback(Value);

			Console.WriteLine(string.Format("END SomeOperationWithCallback() - Counter: {0}, Value: {1} !",MCounter,Value));
		}
//-------------------------------------------------------------------------------------------------------
		public void Dummy()
		{
			Console.WriteLine("DUMMY !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------