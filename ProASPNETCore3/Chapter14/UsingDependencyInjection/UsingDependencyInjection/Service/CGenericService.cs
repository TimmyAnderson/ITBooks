﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! GENERIC CLASS implementuje GENERIC INTERFACE.
	public sealed class CGenericService<TType> : IGenericService<TType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private TType											MValue;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public TType GetValue()
		{
			return(MValue);
		}
//----------------------------------------------------------------------------------------------------------------------
		public void SetValue(TType Value)
		{
			MValue=Value;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------