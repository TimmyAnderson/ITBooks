﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FILTER je mozne aplikovat VIACKRAT.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=true)]
	public sealed class COrderFilter1Attribute : Attribute, IActionFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly string									MPrefix;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public COrderFilter1Attribute(string Prefix)
		{
			MPrefix=Prefix;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuting(ActionExecutingContext Context)
		{
			Console.WriteLine($"{MPrefix} - METHOD [OnActionExecuting()] is CALLED !");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuted(ActionExecutedContext Context)
		{
			Console.WriteLine($"{MPrefix} - METHOD [OnActionExecuted()] is CALLED !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------