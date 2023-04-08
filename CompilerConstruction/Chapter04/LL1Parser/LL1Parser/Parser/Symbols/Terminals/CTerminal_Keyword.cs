﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTerminal_Keyword : CTerminal
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MKeywordLexema;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTerminal_Keyword(string Name, string ScanerTokenID, string TerminalValue, string KeywordLexema)
			: base(Name,ScanerTokenID,TerminalValue)
		{
			MKeywordLexema=KeywordLexema;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											KeywordLexema
		{
			get
			{
				return(MKeywordLexema);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------