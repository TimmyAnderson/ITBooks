﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Service
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CMultiImplementationService2 : IMultiImplementationService
	{
//----------------------------------------------------------------------------------------------------------------------
		public string GetServiceName()
		{
			return("SERVICE CLASS 2");
		}
//----------------------------------------------------------------------------------------------------------------------
		public string GetText()
		{
			return("Hello JENNY !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------