﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CState
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MName;
		private readonly bool									MIsStartState;
		private readonly bool									MIsAcceptingState;
		private readonly bool									MIsErrorState;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		protected CState(string Name, bool IsStartState, bool IsAcceptingState, bool IsErrorState)
		{
			MName=Name;
			MIsStartState=IsStartState;
			MIsAcceptingState=IsAcceptingState;
			MIsErrorState=IsErrorState;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Name
		{
			get
			{
				return(MName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsStartState
		{
			get
			{
				return(MIsStartState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsAcceptingState
		{
			get
			{
				return(MIsAcceptingState);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsErrorState
		{
			get
			{
				return(MIsErrorState);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MName);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------