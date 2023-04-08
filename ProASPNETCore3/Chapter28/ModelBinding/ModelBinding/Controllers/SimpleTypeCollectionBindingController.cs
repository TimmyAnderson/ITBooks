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
	public sealed class SimpleTypeCollectionBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditNames()
		{
			ViewResult											Result=View("EditNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ASP.NET podporuje BINDING COLLECTIONS SIMPLE TYPES.
		[HttpPost]
		public IActionResult EditNameCallback(List<string> Names)
		{
			ViewResult											Result=View("ViewNames",Names.ToArray());

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------