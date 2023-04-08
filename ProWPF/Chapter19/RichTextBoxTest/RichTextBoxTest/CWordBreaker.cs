using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Documents;
//------------------------------------------------------------------------
namespace RichTextBoxTest
{
//------------------------------------------------------------------------
	public static class CWordBreaker
	{
//------------------------------------------------------------------------
        private static TextPointer GetPositionAtWordBoundary(TextPointer Position, LogicalDirection WordBreakDirection)
        {
            if (!Position.IsAtInsertionPosition)
            {
                Position=Position.GetInsertionPosition(WordBreakDirection);
            }

            TextPointer		Navigator=Position;

            while (Navigator!=null && !IsPositionNextToWordBreak(Navigator, WordBreakDirection))
            {
                Navigator=Navigator.GetNextInsertionPosition(WordBreakDirection);
            }

            return(Navigator);
        }
//------------------------------------------------------------------------
        private static bool IsPositionNextToWordBreak(TextPointer Position, LogicalDirection WordBreakDirection)
        {
            bool					IsAtWordBoundary=false;

            if (Position.GetPointerContext(WordBreakDirection)!=TextPointerContext.Text)
            {
                Position=Position.GetInsertionPosition(WordBreakDirection);
            }

            if (Position.GetPointerContext(WordBreakDirection)==TextPointerContext.Text)
            {
                LogicalDirection	OppositeDirection=(WordBreakDirection==LogicalDirection.Forward) ? LogicalDirection.Backward : LogicalDirection.Forward;
                char[]				RunBuffer=new char[1];
                char[]				OppositeRunBuffer=new char[1];

                Position.GetTextInRun(WordBreakDirection, RunBuffer, /*startIndex*/0, /*count*/1);
                Position.GetTextInRun(OppositeDirection, OppositeRunBuffer, /*startIndex*/0, /*count*/1);

                if (RunBuffer[0]==' ' && !(OppositeRunBuffer[0]==' '))
                {
                    IsAtWordBoundary=true;
                }
            }
            else
            {
                IsAtWordBoundary=true;
            }

            return(IsAtWordBoundary);
        }
//------------------------------------------------------------------------
        public static TextRange GetWordRange(TextPointer Position)
        {
            TextRange			WordRange=null;
            TextPointer			WordStartPosition=null;
            TextPointer			WordEndPosition=null;

			WordEndPosition=GetPositionAtWordBoundary(Position, /*wordBreakDirection*/LogicalDirection.Forward);

            if (WordEndPosition != null)
            {
                WordStartPosition=GetPositionAtWordBoundary(WordEndPosition, /*wordBreakDirection*/LogicalDirection.Backward);
            }

            if (WordStartPosition != null && WordEndPosition!=null)
            {
                WordRange = new TextRange(WordStartPosition, WordEndPosition);
            }

            return(WordRange);
        }
//------------------------------------------------------------------------
	}
//------------------------------------------------------------------------
}
//------------------------------------------------------------------------