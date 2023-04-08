using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.Controllers;
using Microsoft.AspNetCore.Mvc.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FILTER je GLOBAL.
	public sealed class CGlobalFilter1 : IActionFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		public CGlobalFilter1()
		{
			Console.WriteLine($"Instance of FILTER [{nameof(CGlobalFilter1)}] is CREATED !");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuting(ActionExecutingContext Context)
		{
			bool												WriteMessage=true;

			if ((Context.ActionDescriptor is ControllerActionDescriptor)==true)
			{
				ControllerActionDescriptor						ActionDescriptor=(ControllerActionDescriptor) Context.ActionDescriptor;

				if (ActionDescriptor.ControllerName=="OrderFilter1" || ActionDescriptor.ControllerName=="OrderFilter2")
				{
					WriteMessage=false;
				}
			}

			if (WriteMessage==true)
			{
				Console.WriteLine($"11111 METHOD [OnActionExecuting()] - GLOBAL FILTER is APPLIED to ACTION METHOD [{Context.ActionDescriptor.DisplayName}] ! 11111");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuted(ActionExecutedContext Context)
		{
			bool												WriteMessage=true;

			if ((Context.ActionDescriptor is ControllerActionDescriptor)==true)
			{
				ControllerActionDescriptor						ActionDescriptor=(ControllerActionDescriptor) Context.ActionDescriptor;

				if (ActionDescriptor.ControllerName=="OrderFilter1" || ActionDescriptor.ControllerName=="OrderFilter2")
				{
					WriteMessage=false;
				}
			}

			if (WriteMessage==true)
			{
				Console.WriteLine($"11111 METHOD [OnActionExecuted()] - GLOBAL FILTER is APPLIED to ACTION METHOD [{Context.ActionDescriptor.DisplayName}] ! 11111");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------