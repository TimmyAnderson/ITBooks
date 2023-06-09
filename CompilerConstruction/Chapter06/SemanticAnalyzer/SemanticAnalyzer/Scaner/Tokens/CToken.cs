﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public class CToken
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MTokenID;
		private readonly string									MLexema;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CToken(string TokenID, string Lexema)
		{
			MTokenID=TokenID;
			MLexema=Lexema;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											TokenID
		{
			get
			{
				return(MTokenID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											Lexema
		{
			get
			{
				return(MLexema);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(Lexema);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------