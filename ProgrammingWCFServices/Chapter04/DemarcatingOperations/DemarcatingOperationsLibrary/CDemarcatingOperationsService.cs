using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.ServiceModel;
//-------------------------------------------------------------------------------------------------------
namespace DemarcatingOperationsLibrary
{
//-------------------------------------------------------------------------------------------------------
	[ServiceBehavior(InstanceContextMode=InstanceContextMode.PerSession)]
	public class CDemarcatingOperationsService : IDemarcatingOperationsContract, IDisposable
	{
//-------------------------------------------------------------------------------------------------------
		private EState											MState;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CDemarcatingOperationsService()
		{
			Console.WriteLine("CDemarcatingOperationsService CONSTRUCTOR called !");

			MState=EState.E_S_UNDEFINED;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Start1()
		{
			EState		NewState=EState.E_S_START_1;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Start1() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Start2()
		{
			EState		NewState=EState.E_S_START_2;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Start2() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside1()
		{
			EState		NewState=EState.E_S_INSIDE_1;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Inside1() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside2()
		{
			EState		NewState=EState.E_S_INSIDE_2;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Inside2() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Inside3()
		{
			EState		NewState=EState.E_S_INSIDE_3;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Inside3() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Terminate1()
		{
			EState		NewState=EState.E_S_TERMINATE_1;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Terminate1() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
		public void Terminate2()
		{
			EState		NewState=EState.E_S_TERMINATE_2;

			Console.WriteLine(string.Format("CDemarcatingOperationsService.Terminate2() called OS: {0}, NS: {1} !",MState,NewState));
			MState=NewState;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Dispose()
		{
			Console.WriteLine("CDemarcatingOperationsService DESTRUCTOR called !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------