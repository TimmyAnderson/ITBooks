﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CTextService1 : ITextService1
	{
//----------------------------------------------------------------------------------------------------------------------
		public string GetText()
		{
			return("Hello TIMMY !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------