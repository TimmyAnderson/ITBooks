﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CovariantsAndContravariants
{
//-------------------------------------------------------------------------------------------------------
	public class CBaseParameter
	{
//-------------------------------------------------------------------------------------------------------
		private int												MNumber;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CBaseParameter(int Number)
		{
			MNumber=Number;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												Number
		{
			get
			{
				return(MNumber);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------