﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//------------------------------------------------------------------------------
namespace MultipleExceptions
{
//------------------------------------------------------------------------------
	public class CAggregateException : Exception
	{
//------------------------------------------------------------------------------
		private List<Exception>					MInnerExceptions;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CAggregateException(IEnumerable<Exception> Exceptions)
		{
			MInnerExceptions=new List<Exception>(Exceptions);
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public Exception[]						InnerExceptions
		{
			get
			{
				return(MInnerExceptions.ToArray());
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------