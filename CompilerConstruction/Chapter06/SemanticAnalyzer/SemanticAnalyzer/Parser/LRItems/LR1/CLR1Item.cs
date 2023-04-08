﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CLR1Item : IEquatable<CLR1Item>
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CLR0Item								MLR0Item;
		private readonly CTerminal								MTerminal;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR1Item(CLR0Item LR0Item, CTerminal Terminal)
		{
			MLR0Item=LR0Item;
			MTerminal=Terminal;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CLR0Item											LR0Item
		{
			get
			{
				return(MLR0Item);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public bool												IsCompleteItem
		{
			get
			{
				return(MLR0Item.IsCompleteItem);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal										Terminal
		{
			get
			{
				return(MTerminal);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSymbol GetSymbolAfterPeriod()
		{
			return(MLR0Item.GetSymbolAfterPeriod());
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsAfterPeriod()
		{
			return(MLR0Item.GetSymbolsAfterPeriod());
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsExceptPeriod()
		{
			return(MLR0Item.GetSymbolsExceptPeriod());
		}
//-------------------------------------------------------------------------------------------------------
		public CSymbol[] GetSymbolsWithIncrementedPeriodPosition()
		{
			return(MLR0Item.GetSymbolsWithIncrementedPeriodPosition());
		}
//-------------------------------------------------------------------------------------------------------
		public bool Equals(CLR1Item Other)
		{
			if (Other==null)
			{
				return(false);
			}

			if (MLR0Item.Equals(Other.MLR0Item)==false)
			{
				return(false);
			}

			if (MTerminal.Equals(Other.MTerminal)==false)
			{
				return(false);
			}
			
			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			StringBuilder		SB=new StringBuilder();

			SB.AppendFormat("[{0}, {1}]",MLR0Item,MTerminal);

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------