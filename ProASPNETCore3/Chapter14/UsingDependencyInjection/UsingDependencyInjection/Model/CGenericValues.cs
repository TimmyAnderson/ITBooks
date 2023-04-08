﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CGenericValues
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly string									MStringValue;
		private readonly int									MIntValue;
		private readonly double									MDoubleValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CGenericValues(string StringValue, int IntValue, double DoubleValue)
		{
			MStringValue=StringValue;
			MIntValue=IntValue;
			MDoubleValue=DoubleValue;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											StringValue
		{
			get
			{
				return(MStringValue);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public int												IntValue
		{
			get
			{
				return(MIntValue);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public double											DoubleValue
		{
			get
			{
				return(MDoubleValue);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------