﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace MethodCallTest
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CBaseClass
	{
//-------------------------------------------------------------------------------------------------------
		public virtual void OverridedMethod()
		{
			Console.WriteLine("BASE - OVERRIDED method CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
		public virtual void OverridedSealedMethod()
		{
			Console.WriteLine("BASE - OVERRIDED SEALED method CALLED !");
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------