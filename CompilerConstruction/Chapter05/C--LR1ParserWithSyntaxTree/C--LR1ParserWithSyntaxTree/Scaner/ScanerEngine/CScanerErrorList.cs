﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace C__LR1ParserWithSyntaxTree
{
//-------------------------------------------------------------------------------------------------------
	public sealed class CScanerErrorList
	{
//-------------------------------------------------------------------------------------------------------
		private List<string>									MErrors;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CScanerErrorList()
		{
			MErrors=new List<string>();
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public bool												HasErrors
		{
			get
			{
				return(MErrors.Count>0);
			}
		}
//-------------------------------------------------------------------------------------------------------
		public string[]											Errors
		{
			get
			{
				return(MErrors.ToArray());
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public void Add(string Error)
		{
			MErrors.Add(Error);
		}
//-------------------------------------------------------------------------------------------------------
		public string GetErrorString()
		{
			StringBuilder				SB=new StringBuilder();

			foreach(string Error in Errors)
			{
				SB.AppendLine(Error);
			}

			return(SB.ToString());
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------