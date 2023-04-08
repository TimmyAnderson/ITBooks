﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
//------------------------------------------------------------------------------
namespace EAP
{
//------------------------------------------------------------------------------
	public class CXXXCompletedEventArgs : AsyncCompletedEventArgs
	{
//------------------------------------------------------------------------------
		private string								MResult;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public CXXXCompletedEventArgs(Exception Error, bool Cancelled, object UserState, string Result)
			: base(Error, Cancelled, UserState)
		{
			MResult=Result;
		}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
		public string								Result
		{
			get
			{
				// Ak je nastavena property Exception, tak ju vyhodi.
				base.RaiseExceptionIfNecessary();

				return(MResult);
			}
		}
//------------------------------------------------------------------------------
	}
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------