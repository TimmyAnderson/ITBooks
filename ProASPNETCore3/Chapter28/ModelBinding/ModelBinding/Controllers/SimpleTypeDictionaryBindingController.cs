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
	public sealed class SimpleTypeDictionaryBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditDictionaryNames()
		{
			ViewResult											Result=View("EditDictionaryNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ASP.NET podporuje BINDING DICTIONARIES SIMPLE TYPES.
		[HttpPost]
		public IActionResult EditNameCallback(Dictionary<string,string> Names)
		{
			ViewResult											Result=View("ViewNames",Names.Values.ToArray());

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------