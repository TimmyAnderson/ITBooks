using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CSourceCode
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MSouceCode;
		private readonly CSourceCodeLine[]						MLines;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSourceCode(string SouceCode)
		{
			MSouceCode=SouceCode;

			List<CSourceCodeLine>								Lines=new List<CSourceCodeLine>();
			StringBuilder										ActualLine=new StringBuilder();
			int													LineIndex=0;

			for (int LineNumber=0;LineNumber<SouceCode.Length;LineNumber++)
			{
				ActualLine.Append(SouceCode[LineNumber]);

				if (SouceCode[LineNumber]=='\n')
				{
					CSourceCodeLine								SourceCodeLine=new CSourceCodeLine(LineIndex,ActualLine.ToString());

					Lines.Add(SourceCodeLine);
					ActualLine.Clear();
					LineIndex=LineNumber+1;
				}
			}

			if (ActualLine.Length>0)
			{
				CSourceCodeLine									SourceCodeLine=new CSourceCodeLine(LineIndex,ActualLine.ToString());

				Lines.Add(SourceCodeLine);
			}

			MLines=Lines.ToArray();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											SouceCode
		{
			get
			{
				return(MSouceCode);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CSourceCodeLine GetSourceCodeLineAtIndex(int Index)
		{
			if (Index<0 || Index>=MSouceCode.Length)
			{
				throw(new CCompilerException("INVALID Index !"));
			}

			CSourceCodeLine										Ret=MLines[0];

			for(int LineNumber=1;LineNumber<MLines.Length;LineNumber++)
			{
				CSourceCodeLine									SourceCodeLine=MLines[LineNumber];

				if (SourceCodeLine.SourceCodeIndex>Index)
				{
					Ret=MLines[LineNumber-1];
					break;
				}
			}

			return(Ret);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------