﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace DiscoverySharedLibrary
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CToUpperService : IToUpperContract
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpper(string Param)
		{
			Console.WriteLine(string.Format("ToUpper(): [{0}] !",Param));

			return(Param.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------