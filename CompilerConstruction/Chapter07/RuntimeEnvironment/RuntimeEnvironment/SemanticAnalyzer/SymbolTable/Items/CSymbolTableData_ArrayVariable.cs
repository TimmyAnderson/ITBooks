﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTableData_ArrayVariable : CSymbolTableData_Variable
	{
//-------------------------------------------------------------------------------------------------------
		private readonly int									MArraySize;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData_ArrayVariable(string SymbolName, ESymbolType SymbolType, int ArraySize)
			: base(SymbolName,SymbolType)
		{
			MArraySize=ArraySize;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public int												ArraySize
		{
			get
			{
				return(MArraySize);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override int GetSizeof()
		{
			return(MArraySize*SymbolType.EXT_GetSizeof(EVariableType.E_VT_LOCAL_VARIABLE));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------