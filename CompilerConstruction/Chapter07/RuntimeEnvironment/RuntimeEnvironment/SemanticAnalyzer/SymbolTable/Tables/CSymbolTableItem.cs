﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace RuntimeEnvironment
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSymbolTableItem
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CSymbolTableData						MSymbolTableData;
		private readonly int									MStackOffset;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableItem(CSymbolTableData SymbolTableData, int StackOffset)
		{
			MSymbolTableData=SymbolTableData;
			MStackOffset=StackOffset;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbolTableData									SymbolTableData
		{
			get
			{
				return(MSymbolTableData);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public int												StackOffset
		{
			get
			{
				return(MStackOffset);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(string.Format("{0}, StackOffset: {1}",SymbolTableData,StackOffset));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------