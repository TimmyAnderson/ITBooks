﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	// !!! This INPUT CHAR MUST BE TESTED for recognition as LAST ONE.
	public class CInputChar_Other : CInputChar
	{
//-------------------------------------------------------------------------------------------------------
		public CInputChar_Other(string Name)
			: base(Name)
		{

		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool IsValidChar(char CharToCheck)
		{
			// All CHARS are ACCEPTED.
			return(true);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------