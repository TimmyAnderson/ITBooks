﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Scaner
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CState_AcceptingError : CState_Accepting
	{
//-------------------------------------------------------------------------------------------------------
		public CState_AcceptingError(string Name)
			: base(Name,true)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------