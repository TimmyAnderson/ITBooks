﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override bool Equals(CSymbol Other)
		{
			if (base.Equals(Other)==false)
			{
				return(false);
			}

			CTerminal_Keyword	OtherTerminalKeyword=Other as CTerminal_Keyword;

			if (OtherTerminalKeyword==null)
			{
				return(false);
			}

			if (MKeywordLexema!=OtherTerminalKeyword.MKeywordLexema)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------