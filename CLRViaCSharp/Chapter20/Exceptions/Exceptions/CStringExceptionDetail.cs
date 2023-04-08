﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//-------------------------------------------------------------------------------------------------------
namespace Exceptions
{
//-------------------------------------------------------------------------------------------------------
	[Serializable]
	public class CStringExceptionDetail : CExceptionDetail
	{
//-------------------------------------------------------------------------------------------------------
		private readonly string									MExceptionText;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public CStringExceptionDetail(string ExceptionText)
		{
			MExceptionText=ExceptionText;
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public string											ExceptionText
		{
			get
			{
				return(MExceptionText);
			}
		}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
		public override string ToString()
		{
			return(MExceptionText);
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------