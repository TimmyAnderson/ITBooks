﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ProtectionLevel
{
//-------------------------------------------------------------------------------------------------------
	public class CSecureContract : ISecureContract
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