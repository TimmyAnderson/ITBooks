﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMultiImplementationService3 : IMultiImplementationService
	{
//----------------------------------------------------------------------------------------------------------------------
		public string GetServiceName()
		{
			return("SERVICE CLASS 3");
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetText()
		{
			return("Hello JOSH !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------