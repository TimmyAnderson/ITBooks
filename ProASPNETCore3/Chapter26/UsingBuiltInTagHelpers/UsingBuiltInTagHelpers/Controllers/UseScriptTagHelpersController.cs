using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseScriptTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScriptAttributes()
		{
			ViewResult											Result=View("UseScriptAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScriptExcluding()
		{
		   ViewResult											Result=View("UseScriptExcluding");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScriptFallback()
		{
		   ViewResult											Result=View("UseScriptFallback");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------