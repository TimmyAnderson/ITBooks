﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace CreatingRESTfulWebServices.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CValidationError
	{
//----------------------------------------------------------------------------------------------------------------------
		private string											MKey;
		private string[]										MErrors;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CValidationError()
		{
			MKey="";
			MErrors=new string[0];
		}
//----------------------------------------------------------------------------------------------------------------------
		public CValidationError(string Key, string[] Errors)
		{
			MKey=Key;
			MErrors=Errors;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public string											Key
		{
			get
			{
				return(MKey);
			}
			set
			{
				MKey=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public string[]											Errors
		{
			get
			{
				return(MErrors);
			}
			set
			{
				MErrors=value;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------