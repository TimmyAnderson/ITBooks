using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//-------------------------------------------------------------------------------------------------------
namespace AsynchronousWCF
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CAsynchronousService : IAsynchronousService
	{
//-------------------------------------------------------------------------------------------------------
		private string ActionSlowOperation(object Parameter)
		{
			Console.WriteLine(string.Format("!!! SERVICE OPERATATION ACTION STARTED !"));

			Thread.Sleep(3000);

			string												TypedParameter=(string) Parameter;
			string												ReturnValue=TypedParameter.ToUpper();

			Console.WriteLine(string.Format("!!! SERVICE OPERATATION ACTION FINIHED !"));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string SlowOperation(string Parameter)
		{
			Console.WriteLine(string.Format("!!! SERVICE OPERATATION STARTED !"));

			Thread.Sleep(3000);

			string												ReturnValue=Parameter.ToUpper();

			Console.WriteLine(string.Format("!!! SERVICE OPERATATION FINIHED !"));

			return(ReturnValue);
		}
//-------------------------------------------------------------------------------------------------------
		// !!! ASYNCHRONOUS FUNCTION pouzita ako WCF OPERATION.
		public async Task<string> AsynchronousSlowOperation(string Parameter)
		{
			Console.WriteLine(string.Format("!!! SERVICE OPERATATION STARTED !"));

			Task<string>										SomeTask=new Task<string>(ActionSlowOperation,Parameter);

			SomeTask.Start();

			await SomeTask;

			Console.WriteLine(string.Format("!!! SERVICE OPERATATION FINIHED !"));

			return(SomeTask.Result);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------