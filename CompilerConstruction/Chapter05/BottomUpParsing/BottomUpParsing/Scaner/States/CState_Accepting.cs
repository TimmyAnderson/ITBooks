﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace BottomUpParsing
{
//-------------------------------------------------------------------------------------------------------
	public class CState_Accepting : CState
	{
//-------------------------------------------------------------------------------------------------------
		protected CState_Accepting(string Name, bool IsErrorState)
			: base(Name,false,true,IsErrorState)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------