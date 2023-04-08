using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ServiceModel;
using System.ServiceModel.Channels;
//-------------------------------------------------------------------------------------------------------
namespace TransportSessionPerCallService
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall,ConcurrencyMode=ConcurrencyMode.Single)]
	public class CSlowServiceNoTS : ISlowContractNoTS, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private string											MID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void SlowOperation(string ID)
		{
			MID=ID;

			Console.WriteLine(string.Format("SlowOperation(): [{0}] - BEGIN [{1}] [{2}] !",ID,this.GetHashCode(),OperationContext.Current.SessionId));

			Thread.Sleep(1*1000);

			Console.WriteLine(string.Format("SlowOperation(): [{0}] - END [{1}] [{2}] !",ID,this.GetHashCode(),OperationContext.Current.SessionId));
		}
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(string.Format("Dispose(): [{0}] - BEGIN !",MID));

			Thread.Sleep(1*1000);

			Console.WriteLine(string.Format("Dispose(): [{0}] - END !",MID));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------