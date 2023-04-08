﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CSymbolTableData
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MSymbolName;
		private readonly ESymbolType							MSymbolType;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData(string SymbolName, ESymbolType SymbolType)
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
		public abstract int GetSizeof();
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