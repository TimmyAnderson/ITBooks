using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CScanerEngine
	{
//-------------------------------------------------------------------------------------------------------
		private readonly CState									MStateStart;
		private readonly CState_AcceptingTokenEOF				MStateEOF;
		private readonly CState[]								MStates;
		private readonly bool									MLogWhiteCharsAndComments;
		private readonly StringBuilder							MLog;
//-------------------------------------------------------------------------------------------------------
		private CState											MActualState;
		private StringBuilder									MSourceCode;
		private int												MActualSourceCodeIndex;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CScanerEngine(CState[] States, bool LogWhiteCharsAndComments)
		{
			CState									StateStart=States.Where(P => P.IsStartState==true).FirstOrDefault();
			CState_AcceptingTokenEOF				StateEOF=States.Where(P => P.IsAcceptingState==true && P.GetType()==typeof(CState_AcceptingTokenEOF)).OfType<CState_AcceptingTokenEOF>().FirstOrDefault();

			if (StateStart==null)
				throw(new ArgumentException("States DOESN'T CONTAIN START state !"));

			if (States.Where(P => P.IsAcceptingState==true).Count()==0)
				throw(new ArgumentException("States DOESN'T CONTAIN ACCEPTING state !"));

			if (StateEOF==null)
				throw(new ArgumentException("States DOESN'T CONTAIN EOF state !"));

			MStateStart=StateStart;
			MStateEOF=StateEOF;
			MStates=States;
			MLogWhiteCharsAndComments=LogWhiteCharsAndComments;
			MLog=new StringBuilder();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											Log
		{
			get
			{
				return(MLog.ToString());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		private CToken GetNextToken(CCompilerErrorCollection Errors)
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

					Errors.AddError(new CScaningError(ErrorMessage));
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
						CToken_Keyword				Token=new CToken_Keyword(ActualState.KeywordTokenID,ParsedLexema,LastValidTokenPosition);

						return(Token);
					}
					else
					{
						CToken_Identifier			Token=new CToken_Identifier(ActualState.NonKeywordTokenID,ParsedLexema,LastValidTokenPosition);

						return(Token);
					}
				}
				else
				{
					CState_AcceptingToken			ActualState=(CState_AcceptingToken) MActualState;
					string							TokenID=ActualState.TokenID;
					CToken							Token=new CToken(TokenID,ParsedLexema,LastValidTokenPosition);

					return(Token);
				}
			}
			else
			{
				string								ErrorInSourceCode=MSourceCode.ToString().Substring(LastValidTokenPosition);
				string								ErrorMessage=string.Format("TOKEN was NOT FOUND. Error near [{0}] !",ErrorInSourceCode);

				Errors.AddError(new CScaningError(ErrorMessage));
				return(null);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool Scan(CSourceCode SourceCode, CTokenCollection TokenCollection, CCompilerErrorCollection Errors)
		{
			TokenCollection.Clear();
			MLog.Clear();

			MSourceCode=new StringBuilder(SourceCode.SouceCode);
			MActualSourceCodeIndex=0;

			while(MActualSourceCodeIndex<MSourceCode.Length)
			{
				CToken								Token=GetNextToken(Errors);

				if (Token!=null)
				{
					TokenCollection.AddToken(Token);

					if (MLogWhiteCharsAndComments==true || (Token.TokenID!="WHITE CHARS" && Token.TokenID!="COMMENT"))
					{
						MLog.AppendLine(string.Format("TYPE: [{0}], TOKEN: [{1}] !",Token.TokenID,Token.Lexema));
					}
				}
				else
				{
					TokenCollection.Clear();

					MLog.AppendLine(string.Format("SCANER FAILED !"));

					return(false);
				}
			}

			CToken							TokenEOF=new CToken(MStateEOF.TokenID,"$",0);

			TokenCollection.AddToken(TokenEOF);

			MLog.AppendLine(string.Format("SCANER COMPLETED SUCCESSFULLY !"));

			return(true);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------