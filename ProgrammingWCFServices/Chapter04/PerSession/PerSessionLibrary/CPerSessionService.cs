using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerSessionLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CPerSessionService : IPerSessionContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private CState											MState;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerSessionService()
		{
			Console.WriteLine("CPerSessionService CONSTRUCTOR called !");

			// Nejaky default state.
			if (MState==null)
				MState=new CState(-1,"NOT DEFINED");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState()
		{
			Console.WriteLine(string.Format("CPerSessionService.GetState() called (ID: {0}) !",OperationContext.Current.SessionId));
			return(MState);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState(CState State)
		{
			Console.WriteLine(string.Format("CPerSessionService.SetState() called (ID: {0}) !",OperationContext.Current.SessionId));
			MState=State;
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState()
		{
			Console.WriteLine(string.Format("CPerSessionService.PrintActualState() called (ID: {0}) !",OperationContext.Current.SessionId));
			
			Console.WriteLine(string.Format("ActualState: {0} !",MState));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CPerSessionService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------