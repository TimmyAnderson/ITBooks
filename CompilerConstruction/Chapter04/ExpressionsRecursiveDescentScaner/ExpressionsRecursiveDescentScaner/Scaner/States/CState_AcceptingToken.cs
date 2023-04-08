﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ExpressionsRecursiveDescentScaner
{
//-------------------------------------------------------------------------------------------------------
	public class CState_AcceptingToken : CState_Accepting
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MTokenID;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CState_AcceptingToken(string Name, string TokenID)
			: base(Name,false)
		{
			MTokenID=TokenID;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											TokenID
		{
			get
			{
				return(MTokenID);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------