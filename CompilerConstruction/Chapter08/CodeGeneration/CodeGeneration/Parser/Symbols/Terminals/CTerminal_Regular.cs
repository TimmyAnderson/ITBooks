﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTerminal_Regular : CTerminal
	{
//-------------------------------------------------------------------------------------------------------
		public CTerminal_Regular(string Name, string ScanerTokenID, string TerminalValue)
			: base(Name,ScanerTokenID,TerminalValue)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------