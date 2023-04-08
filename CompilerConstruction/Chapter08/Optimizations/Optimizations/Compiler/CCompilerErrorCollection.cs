using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Optimizations
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CCompilerErrorCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CCompilerError>					MParsingErrors;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CCompilerErrorCollection()
		{
			MParsingErrors=new List<CCompilerError>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool												HasErrors
		{
			get
			{
				return(MParsingErrors.Count>0);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void AddError(CCompilerError ParsingError)
		{
			MParsingErrors.Add(ParsingError);
		}
//-------------------------------------------------------------------------------------------------------
		public void AddErrors(CCompilerError[] ParsingErrors)
		{
			foreach(CCompilerError ParsingError in ParsingErrors)
			{
				MParsingErrors.Add(ParsingError);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public void Clear()
		{
			MParsingErrors.Clear();
		}
//-------------------------------------------------------------------------------------------------------
		public string GetAllErrors(CSourceCode SourceCode)
		{
			StringBuilder										SB=new StringBuilder();
			int													Counter=0;

			foreach(CCompilerError ParsingError in MParsingErrors)
			{
				string											ErrorType;

				if ((ParsingError is CScaningError)==true)
				{
					ErrorType="SCANING ERROR";
				}
				else if ((ParsingError is CParsingError)==true)
				{
					ErrorType="PARSING ERROR";
				}
				else if ((ParsingError is CSemanticError)==true)
				{
					ErrorType="SEMANTIC ERROR";
				}
				else
				{
					ErrorType="COMPILER ERROR";
				}

				SB.AppendLine(string.Format("{0}. {1} - {2} !",++Counter,ErrorType,ParsingError.GetError(SourceCode)));
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------