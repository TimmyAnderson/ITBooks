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
	public sealed class UseLinkTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseLinkAttributes()
		{
			ViewResult											Result=View("UseLinkAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseLinkExcluding()
		{
			ViewResult											Result=View("UseLinkExcluding");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseLinkFallback()
		{
			ViewResult											Result=View("UseLinkFallback");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------