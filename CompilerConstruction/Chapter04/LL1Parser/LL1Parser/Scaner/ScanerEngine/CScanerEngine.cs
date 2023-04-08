using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace LL1Parser
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CScanerEngine
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CState									MStateStart;
		private readonly CState_AcceptingTokenEOF				MStateEOF;
		private readonly CState[]								MStates;
//-------------------------------------------------------------------------------------------------------
		private CState											MActualState;
		private StringBuilder									MSourceCode;
		private int												MActualSourceCodeIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CScanerEngine(CState[] States)
		{
			CState									StateStart=States.Where(P => P.IsStartState==true).FirstOrDefault();
			CState_AcceptingTokenEOF				StateEOF=States.Where(P => P.IsAcceptingState==true && P.GetType()==typeof(CState_AcceptingTokenEOF)).OfType<CState_AcceptingTokenEOF>().FirstOrDefault();

			if (StateStart==null)
				throw(new ArgumentException("States DOESN'T CONTAIN START state !"));

			if (States.Where(P => P.IsAcceptingState==true).Count()==0)
				throw(new ArgumentException("States DOESN'T CONTAIN ACCEPTING state !"));

			MStateStart=StateStart;
			MStateEOF=StateEOF;
			MStates=States;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CToken GetNextToken(CScanerErrorList Errors)
		{
			MActualState=MStateStart;

			int										LastValidTokenPosition=MActualSourceCodeIndex;
			StringBuilder							Lexema=new StringBuilder();
			char									NewChar;

			while(MActualState.IsAcceptingState==false)
			{
				if (MActualSourceCodeIndex>MSourceCode.Length)
				{
					string							ErrorMessage=string.Format("SCANER has REACHED END of SOURCE CODE !");

					Errors.Add(ErrorMessage);
					return(null);
				}

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
					Lexema.Append(NewChar);
				}

				MActualState=Transition.NewState;
			}

			if (MActualState.IsErrorState==false)
			{
				string								ParsedLexema=Lexema.ToString();

				if ((MActualState is CState_AcceptingKeywordToken)==true)
				{
					CState_AcceptingKeywordToken	ActualState=(CState_AcceptingKeywordToken) MActualState;

					if (ActualState.CheckLexemaForKeyword(ParsedLexema)==true)
					{
						CToken_Keyword				Token=new CToken_Keyword(ActualState.KeywordTokenID,ParsedLexema);

						return(Token);
					}
					else
					{
						CToken						Token=new CToken(ActualState.NonKeywordTokenID,ParsedLexema);

						return(Token);
					}
				}
				else
				{
					CState_AcceptingToken			ActualState=(CState_AcceptingToken) MActualState;
					string							TokenID=ActualState.TokenID;
					CToken							Token=new CToken(TokenID,ParsedLexema);

					return(Token);
				}
			}
			else
			{
				string								ErrorInSourceCode=MSourceCode.ToString().Substring(LastValidTokenPosition);
				string								ErrorMessage=string.Format("TOKEN was NOT FOUND. Error near [{0}] !",ErrorInSourceCode);

				Errors.Add(ErrorMessage);
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CToken[] GetAllTokens(string SourceCode, CScanerErrorList Errors)
		{
			bool									WasError=false;
			List<CToken>							Tokens=new List<CToken>();

			MSourceCode=new StringBuilder(SourceCode);
			MActualSourceCodeIndex=0;

			while(MActualSourceCodeIndex<MSourceCode.Length)
			{
				CToken								Token=GetNextToken(Errors);

				if (Token!=null)
				{
					Tokens.Add(Token);
				}
				else
				{
					WasError=true;
					break;
				}
			}

			MSourceCode=null;
			MActualSourceCodeIndex=0;

			if (WasError==false)
			{
				CToken							TokenEOF=new CToken(MStateEOF.TokenID,"");

				Tokens.Add(TokenEOF);
				return(Tokens.ToArray());
			}
			else
			{
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------