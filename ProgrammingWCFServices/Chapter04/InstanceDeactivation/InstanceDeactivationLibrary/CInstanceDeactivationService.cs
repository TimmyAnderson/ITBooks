using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace InstanceDeactivationLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CInstanceDeactivationService : IInstanceDeactivationContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private static Random									MRND=new Random();
//-------------------------------------------------------------------------------------------------------
		private int												MValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInstanceDeactivationService()
		{
			MValue=MRND.Next(-1000,-1);
			Console.WriteLine(string.Format("CInstanceDeactivationService CONSTRUCTOR called (Value: {0}) !",MValue));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.None)]
		public void StartSession(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService.StartSession() called (Old: {0}, New: {1}) !",MValue,Value));
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.BeforeCall)]
		public void BeforeCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService.BeforeCall() called (Old: {0}, New: {1}) !",MValue,Value));
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.AfterCall)]
		public void AfterCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService.AfterCall() called (Old: {0}, New: {1}) !",MValue,Value));
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.BeforeAndAfterCall)]
		public void BeforeAndAfterCall(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService.BeforeAndAfterCall() called (Old: {0}, New: {1}) !",MValue,Value));
			MValue=Value;
		}
//-------------------------------------------------------------------------------------------------------
		[OperationBehavior(ReleaseInstanceMode=ReleaseInstanceMode.None)]
		public void ManualRelease(int Value)
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService.ManualRelease() called (Old: {0}, New: {1}) !",MValue,Value));
			MValue=Value;
			OperationContext.Current.InstanceContext.ReleaseServiceInstance();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine(string.Format("CInstanceDeactivationService DESTRUCTOR called (Value: {0}) and OPERATION CONTEXT is [{1}] !",MValue,(OperationContext.Current!=null) ? "NOT NULL" : "NULL"));
			Console.WriteLine();
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------