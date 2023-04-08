using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class SimpleTypeArrayBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditNames()
		{
			ViewResult											Result=View("EditNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditIndexedNames()
		{
			ViewResult											Result=View("EditIndexedNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ASP.NET podporuje BINDING ARRAYS SIMPLE TYPES.
		[HttpPost]
		public IActionResult EditNameCallback(string[] Names)
		{
			ViewResult											Result=View("ViewNames",Names);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------