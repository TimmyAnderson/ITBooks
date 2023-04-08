using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseAnchorTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseAnchorAttributes()
		{
			ViewResult											Result=View("UseAnchorAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------