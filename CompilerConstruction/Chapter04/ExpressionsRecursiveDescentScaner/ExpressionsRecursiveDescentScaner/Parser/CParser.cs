using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ExpressionsRecursiveDescentScaner
{
//-------------------------------------------------------------------------------------------------------
	public class CParser
	{
//-------------------------------------------------------------------------------------------------------
		private static string									TOKEN_ID_NUMBER="NUMBER";
		private static string									TOKEN_ID_PLUS="PLUS";
		private static string									TOKEN_ID_MINUS="MINUS";
		private static string									TOKEN_ID_ASTERISK="ASTERISK";
		private static string									TOKEN_ID_SLASH="SLASH";
		private static string									TOKEN_ID_ROUND_BRACKET_LEFT="ROUND BRACKET LEFT";
		private static string									TOKEN_ID_ROUND_BRACKET_RIGHT="ROUND BRACKET RIGHT";
//-------------------------------------------------------------------------------------------------------
		private CToken[]										MTokens;
		private int												MTokenPosition;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParser(CToken[] Tokens)
		{
			MTokens=Tokens;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CToken											ActualToken
		{
			get
			{
				return(MTokens[MTokenPosition]);
			}
		}
//-------------------------------------------------------------------------------------------------------
		private bool											IsBeyondLastToken
		{
			get
			{
				return(MTokenPosition>=MTokens.Length);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private void DoTokenIDCheck(string TokenID)
		{
			if (IsBeyondLastToken==true)
				throw(new InvalidOperationException(string.Format("PARSE ERROR - END of TOKEN ARRAY REACHED !")));

			if (ActualToken.TokenID==TokenID)
			{
				MTokenPosition++;
			}
			else
			{
				throw(new InvalidOperationException(string.Format("PARSE ERROR near [{0}] !",ActualToken)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		// RULE: EXP -> TERM {ADD_OP TERM}.
		private int EXP()
		{
			// Parsuje NON-TERMINAL 'TERM'.
			int					Value=TERM();

			// Realizuje OPAKOVANIE - SYNTAX '{}' v EBNF RULE.
			while(IsBeyondLastToken==false && (ActualToken.TokenID==TOKEN_ID_PLUS || ActualToken.TokenID==TOKEN_ID_MINUS))
			{
				if (ActualToken.TokenID==TOKEN_ID_PLUS)
				{
					// Parsuje TERMINAL '+'.
					DoTokenIDCheck(TOKEN_ID_PLUS);

					// Parsuje NON-TERMINAL 'TERM'.
					Value+=TERM();
				}
				else
				{
					// Parsuje TERMINAL '-'.
					DoTokenIDCheck(TOKEN_ID_MINUS);

					// Parsuje NON-TERMINAL 'TERM'.
					Value-=TERM();
				}
			}

			return(Value);
		}
//-------------------------------------------------------------------------------------------------------
		// RULE: TERM -> FACTOR {MUL_OP FACTOR}.
		private int TERM()
		{
			int					Value=FACTOR();

			// Realizuje OPAKOVANIE - SYNTAX '{}' v EBNF RULE.
			while(IsBeyondLastToken==false && (ActualToken.TokenID==TOKEN_ID_ASTERISK || ActualToken.TokenID==TOKEN_ID_SLASH))
			{
				if (ActualToken.TokenID==TOKEN_ID_ASTERISK)
				{
					// Parsuje TERMINAL '*'.
					DoTokenIDCheck(TOKEN_ID_ASTERISK);

					// Parsuje NON-TERMINAL 'FACTOR'.
					Value*=FACTOR();
				}
				else
				{
					// Parsuje TERMINAL '/'.
					DoTokenIDCheck(TOKEN_ID_SLASH);

					// Parsuje NON-TERMINAL 'FACTOR'.
					Value/=FACTOR();
				}
			}

			return(Value);
		}
//-------------------------------------------------------------------------------------------------------
		// RULE: FACTOR -> '(' EXP ')' | 'NUMBER' | '-NUMBER'.
		private int FACTOR()
		{
			if (IsBeyondLastToken==true)
				throw(new InvalidOperationException(string.Format("PARSE ERROR - END of TOKEN ARRAY REACHED !")));

			if (ActualToken.TokenID==TOKEN_ID_ROUND_BRACKET_LEFT)
			{
				int				Value;

				// Parsuje TERMINAL '('.
				DoTokenIDCheck(TOKEN_ID_ROUND_BRACKET_LEFT);

				// Parsuje NON-TERMINAL 'EXP'.
				Value=EXP();

				// Parsuje TERMINAL ')'.
				DoTokenIDCheck(TOKEN_ID_ROUND_BRACKET_RIGHT);

				return(Value);
			}
			else if (ActualToken.TokenID==TOKEN_ID_NUMBER)
			{
				// Parsuje TERMINAL 'NUMBER'.
				int				Value=int.Parse(ActualToken.Lexema);

				DoTokenIDCheck(TOKEN_ID_NUMBER);

				return(Value);
			}
			else if (ActualToken.TokenID==TOKEN_ID_MINUS)
			{
				// Parsuje TERMINAL '-'.
				DoTokenIDCheck(TOKEN_ID_MINUS);

				// Parsuje TERMINAL 'NUMBER'.
				int				Value=int.Parse(ActualToken.Lexema);

				Value*=-1;

				DoTokenIDCheck(TOKEN_ID_NUMBER);

				return(Value);
			}
			else
			{
				throw(new InvalidOperationException(string.Format("PARSE ERROR near [{0}] !",ActualToken)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void DoParse()
		{
			MTokenPosition=0;

			try
			{
				int				Result=EXP();

				Console.WriteLine();
				Console.WriteLine(string.Format("PARSING RESULT: [{0}] !",Result));
			}
			catch(Exception E)
			{
				Console.WriteLine(string.Format("EXCEPTION: [{0}] !",E.Message));
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------