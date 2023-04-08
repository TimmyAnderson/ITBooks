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
	public sealed class UseEnvironmentTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseEnvironmentAttributes()
		{
		   ViewResult											Result=View("UseEnvironmentAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------