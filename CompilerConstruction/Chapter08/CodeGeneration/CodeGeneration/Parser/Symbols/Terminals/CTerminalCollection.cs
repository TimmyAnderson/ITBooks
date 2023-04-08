using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CTerminalCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CTerminal>						MTerminals;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTerminalCollection()
		{
			MTerminals=new List<CTerminal>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CTerminal[]										Terminals
		{
			get
			{
				return(MTerminals.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal[]										TerminalsButEmpty
		{
			get
			{
				return(MTerminals.Where(P => P.GetType()!=typeof(CTerminal_EMPTY)).ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddTerminal(CTerminal Terminal)
		{
			MTerminals.Add(Terminal);
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal FindTerminalByTerminalValue(string TerminalValue)
		{
			CTerminal		Terminal=MTerminals.Where(P => P.TerminalValue==TerminalValue).FirstOrDefault();

			if (Terminal!=null)
				return(Terminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find TERMINAL for TERMINAL VALUE [{0}] !",TerminalValue)));
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal FindTerminalByScanerTokenID(string ScanerTokenID)
		{
			CTerminal		Terminal=MTerminals.Where(P => P.ScanerTokenID==ScanerTokenID).FirstOrDefault();

			if (Terminal!=null)
				return(Terminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find TERMINAL for SCANER TOKEN ID [{0}] !",ScanerTokenID)));
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal FindTerminalByScanerToken(CToken Token)
		{
			CTerminal		Terminal=MTerminals.Where(P => P.ScanerTokenID==Token.TokenID && P.TerminalValue==Token.Lexema).FirstOrDefault();

			if (Terminal==null)
			{
				Terminal=MTerminals.Where(P => P.ScanerTokenID==Token.TokenID).FirstOrDefault();
			}

			if (Terminal!=null)
				return(Terminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find TERMINAL for SCANER TOKEN [{0}] !",Token)));
		}
//-------------------------------------------------------------------------------------------------------
		public CTerminal FindTerminalByType(Type TerminalType)
		{
			CTerminal		Terminal=MTerminals.Where(P => P.GetType()==TerminalType).FirstOrDefault();

			if (Terminal!=null)
				return(Terminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find TERMINAL TYPE [{0}] !",TerminalType)));
		}
//-------------------------------------------------------------------------------------------------------
		public TTerminalType FindTerminalByType<TTerminalType>() where TTerminalType : CTerminal
		{
			TTerminalType			Terminal=(TTerminalType) MTerminals.Where(P => P.GetType()==typeof(TTerminalType)).FirstOrDefault();

			if (Terminal!=null)
				return(Terminal);
			else
				throw(new InvalidOperationException(string.Format("Can't find TERMINAL TYPE [{0}] !",typeof(TTerminalType))));
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------