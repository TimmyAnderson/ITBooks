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
	public sealed class UseUrlResolutionTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseUrlResolutionAttributes()
		{
			ViewResult											Result=View("UseUrlResolutionAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------