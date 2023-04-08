using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace ExpressionsRecursiveDescentScaner
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CScaner
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CState									MStartState;
		private readonly CState[]								MStates;
//-------------------------------------------------------------------------------------------------------
		private CState											MActualState;
		private StringBuilder									MSourceCode;
		private int												MActualSourceCodeIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CScaner(CState[] States)
		{
			CState									StartState=States.Where(P => P.IsStartState==true).FirstOrDefault();

			if (StartState==null)
				throw(new ArgumentException("States DOESN'T CONTAIN START state !"));

			if (States.Where(P => P.IsAcceptingState==true).Count()==0)
				throw(new ArgumentException("States DOESN'T CONTAIN ACCEPTING state !"));

			MStartState=StartState;
			MStates=States;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CToken GetNextToken()
		{
			MActualState=MStartState;

			int										LastValidTokenPosition=MActualSourceCodeIndex;
			CToken									Token=new CToken();

			while(MActualState.IsAcceptingState==false)
			{
				if (MActualSourceCodeIndex>MSourceCode.Length)
					throw(new InvalidOperationException(string.Format("SCANER has REACHED END of SOURCE CODE !")));

				char								NewChar;

				if (MActualSourceCodeIndex<MSourceCode.Length)
					NewChar=MSourceCode[MActualSourceCodeIndex];
				else
					NewChar=CInputChar_EOF.EOF;
				
				CState_NonAccepting					ActualState=(CState_NonAccepting) MActualState;
				CTransition							Transition=ActualState.GetMatchingTransition(NewChar);

				if (Transition==null)
					throw(new InvalidOperationException(string.Format("CAN'T find TRANSITION from state [{0}] for char [{1}] !",MActualState,NewChar)));

				if (Transition.IsConsumingCharTransition==true)
				{
					MActualSourceCodeIndex++;
					Token.AddChar(NewChar);
				}

				MActualState=Transition.NewState;
			}

			if (MActualState.IsErrorState==false)
			{
				if ((MActualState is CState_AcceptingKeywordToken)==true)
				{
					CState_AcceptingKeywordToken	ActualState=(CState_AcceptingKeywordToken) MActualState;

					if (ActualState.CheckLexemaForKeyword(Token.Lexema)==true)
						Token.TokenID=ActualState.KeywordTokenID;
					else
						Token.TokenID=ActualState.NonKeywordTokenID;
				}
				else
				{
					CState_AcceptingToken			ActualState=(CState_AcceptingToken) MActualState;

					Token.TokenID=ActualState.TokenID;
				}

				return(Token);
			}
			else
			{
				string								ErrorInSourceCode=MSourceCode.ToString().Substring(LastValidTokenPosition);

				throw(new InvalidOperationException(string.Format("TOKEN was NOT FOUND. Error near [{0}] !",ErrorInSourceCode)));
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CToken[] GetAllTokens(string SourceCode)
		{
			MSourceCode=new StringBuilder(SourceCode);
			MActualSourceCodeIndex=0;

			List<CToken>						Tokens=new List<CToken>();

			try
			{
				while(MActualSourceCodeIndex<MSourceCode.Length)
				{
					CToken						Token=GetNextToken();

					Tokens.Add(Token);
				}

				return(Tokens.ToArray());
			}
			finally
			{
				MSourceCode=null;
				MActualSourceCodeIndex=0;
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------