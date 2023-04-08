﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbolTableItem
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MSymbolName;
		private readonly ESymbolType							MSymbolType;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem(string SymbolName, ESymbolType SymbolType)
		{
			MSymbolName=SymbolName;
			MSymbolType=SymbolType;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											SymbolName
		{
			get
			{
				return(MSymbolName);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public ESymbolType										SymbolType
		{
			get
			{
				return(MSymbolType);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("{0} {1}",SymbolType.EXT_GetFriendlyName(),SymbolName));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------