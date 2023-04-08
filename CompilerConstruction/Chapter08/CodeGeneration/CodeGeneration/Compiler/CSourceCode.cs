using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace CodeGeneration
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

			for (int i=0;i<SouceCode.Length;i++)
			{
				ActualLine.Append(SouceCode[i]);

				if (SouceCode[i]=='\n')
				{
					CSourceCodeLine								SourceCodeLine=new CSourceCodeLine(LineIndex,ActualLine.ToString());

					Lines.Add(SourceCodeLine);
					ActualLine.Clear();
					LineIndex=i+1;
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
				throw(new ArgumentException("INVALID Index !"));
			}

			CSourceCodeLine										Ret=MLines[0];

			for(int i=1;i<MLines.Length;i++)
			{
				CSourceCodeLine									SourceCodeLine=MLines[i];

				if (SourceCodeLine.SourceCodeIndex>Index)
				{
					Ret=MLines[i-1];
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