﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ProtectionLevel
{
//-------------------------------------------------------------------------------------------------------
	public class CNonSecureContract : INonSecureContract
	{
//-------------------------------------------------------------------------------------------------------
		public string ToUpper(string Value)
		{
			return(Value.ToUpper());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------