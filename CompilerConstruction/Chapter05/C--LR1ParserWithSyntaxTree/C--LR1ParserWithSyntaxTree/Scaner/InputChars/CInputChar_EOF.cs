﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public class CInputChar_EOF : CInputChar
	{
//-------------------------------------------------------------------------------------------------------
		public static readonly char								EOF='\0';
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CInputChar_EOF(string Name)
			: base(Name)
		{
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool IsValidChar(char CharToCheck)
		{
			if (CharToCheck==EOF)
				return(true);
			else
				return(false);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------