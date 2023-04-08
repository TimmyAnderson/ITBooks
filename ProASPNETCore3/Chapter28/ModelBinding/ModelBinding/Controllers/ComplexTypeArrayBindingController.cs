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
	public sealed class ComplexTypeArrayBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditSimpleChildren()
		{
			ViewResult											Result=View("EditSimpleChildren");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! ASP.NET podporuje BINDING ARRAYS COMPLEX TYPES.
		[HttpPost]
		public IActionResult EditSimpleChildrenCallback(CSimpleChild[] Children)
		{
			ViewResult											Result=View("ViewSimpleChildren",Children);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------