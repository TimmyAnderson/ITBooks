﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public class CToken_Keyword : CToken
	{
//-------------------------------------------------------------------------------------------------------
		public CToken_Keyword(string TokenID, string Lexema)
			: base(TokenID,Lexema)
		{
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------