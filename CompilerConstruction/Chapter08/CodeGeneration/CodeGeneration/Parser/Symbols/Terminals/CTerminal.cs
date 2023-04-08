﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public abstract class CTerminal : CSymbol
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MScanerTokenID;
		private readonly string									MTerminalValue;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTerminal(string Name, string ScanerTokenID, string TerminalValue)
			: base(Name)
		{
			MScanerTokenID=ScanerTokenID;
			MTerminalValue=TerminalValue;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											ScanerTokenID
		{
			get
			{
				return(MScanerTokenID);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string											TerminalValue
		{
			get
			{
				return(MTerminalValue);
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

			CTerminal				OtherTerminal=Other as CTerminal;

			if (OtherTerminal==null)
			{
				return(false);
			}

			if (MScanerTokenID!=OtherTerminal.MScanerTokenID)
			{
				return(false);
			}

			if (MTerminalValue!=OtherTerminal.MTerminalValue)
			{
				return(false);
			}

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MTerminalValue);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------