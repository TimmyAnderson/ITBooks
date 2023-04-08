using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace SingletonLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.Single)]
	public class CSingletonService : ISingletonContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private CState											MState;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSingletonService()
		{
			Console.WriteLine("CSingletonService CONSTRUCTOR called !");

			// Nejaky default state.
			if (MState==null)
				MState=new CState(-1,"NOT DEFINED");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState()
		{
			Console.WriteLine(string.Format("CSingletonService.GetState() called (ID: {0}) !",OperationContext.Current.SessionId));
			return(MState);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState(CState State)
		{
			Console.WriteLine(string.Format("CSingletonService.SetState() called (ID: {0}) !",OperationContext.Current.SessionId));
			MState=State;
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState()
		{
			Console.WriteLine(string.Format("CSingletonService.PrintActualState() called (ID: {0}) !",OperationContext.Current.SessionId));
			
			Console.WriteLine(string.Format("ActualState: {0} !",MState));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CSingletonService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------