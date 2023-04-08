using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace PerCallLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerCall)]
	public class CPerCallService : IPerCallContract1, IPerCallContract2, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private CState											MState1;
		private CState											MState2;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CPerCallService()
		{
			Console.WriteLine("CPerCallService CONSTRUCTOR called !");

			// Nejaky default state.
			if (MState1==null)
				MState1=new CState(-1,"NOT DEFINED");

			if (MState2==null)
				MState2=new CState(-1,"NOT DEFINED");
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState GetState1()
		{
			Console.WriteLine(string.Format("CPerCallService.GetState1() called (ID: {0}) !",OperationContext.Current.SessionId));
			return(MState1);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState1(CState State)
		{
			Console.WriteLine(string.Format("CPerCallService.SetState1() called (ID: {0}) !",OperationContext.Current.SessionId));
			MState1=State;
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState1()
		{
			Console.WriteLine(string.Format("CPerCallService.PrintActualState1() called (ID: {0}) !",OperationContext.Current.SessionId));
			
			Console.WriteLine(string.Format("ActualState1: {0} !",MState1));
		}
//-------------------------------------------------------------------------------------------------------
		public CState GetState2()
		{
			Console.WriteLine(string.Format("CPerCallService.GetState2() called (ID: {0}) !",OperationContext.Current.SessionId));
			return(MState2);
		}
//-------------------------------------------------------------------------------------------------------
		public void SetState2(CState State)
		{
			Console.WriteLine(string.Format("CPerCallService.SetState2() called (ID: {0}) !",OperationContext.Current.SessionId));
			MState2=State;
		}
//-------------------------------------------------------------------------------------------------------
		public void PrintActualState2()
		{
			Console.WriteLine(string.Format("CPerCallService.PrintActualState2() (ID: {0}) called !",OperationContext.Current.SessionId));
			
			Console.WriteLine(string.Format("ActualState2: {0} !",MState2));
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CPerCallService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------