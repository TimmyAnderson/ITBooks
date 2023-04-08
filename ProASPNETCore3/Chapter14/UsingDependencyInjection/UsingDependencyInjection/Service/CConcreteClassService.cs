﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Model
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CConcreteClassService
	{
//----------------------------------------------------------------------------------------------------------------------
		public string PrepareMessage(string Message)
		{
			string												Result=$"[{DateTime.Now}] - CConcreteClassService - [{Message}] !";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------