﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTerminal_EMPTY : CTerminal
	{
//-------------------------------------------------------------------------------------------------------
		public CTerminal_EMPTY(string Name, string ScanerTokenID, string TerminalValue)
			: base(Name,ScanerTokenID,TerminalValue)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------