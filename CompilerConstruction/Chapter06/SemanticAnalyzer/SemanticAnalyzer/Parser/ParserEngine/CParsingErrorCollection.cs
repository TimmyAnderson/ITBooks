﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace SemanticAnalyzer
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CParsingErrorCollection
	{
//-------------------------------------------------------------------------------------------------------
		private readonly List<CParsingError>					MParsingErrors;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CParsingErrorCollection()
		{
			MParsingErrors=new List<CParsingError>();
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
		public void AddParsingError(CParsingError ParsingError)
		{
			MParsingErrors.Add(ParsingError);
		}
//-------------------------------------------------------------------------------------------------------
		public string PrintAllErrors()
		{
			StringBuilder			SB=new StringBuilder();
			int						Counter=1;

			foreach(CParsingError ParsingError in MParsingErrors)
			{
				SB.AppendLine(string.Format("{0}. ERROR: [{1}] !",Counter++,ParsingError.ToString()));
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
 			 return(PrintAllErrors());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------