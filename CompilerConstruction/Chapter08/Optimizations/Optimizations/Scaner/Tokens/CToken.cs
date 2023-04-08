﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public class CToken
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MTokenID;
		private readonly string									MLexema;
		private readonly int									MSourceCodeIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CToken(string TokenID, string Lexema, int SourceCodeIndex)
		{
			MTokenID=TokenID;
			MLexema=Lexema;
			MSourceCodeIndex=SourceCodeIndex;
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
		public int												SourceCodeIndex
		{
			get
			{
				return(MSourceCodeIndex);
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