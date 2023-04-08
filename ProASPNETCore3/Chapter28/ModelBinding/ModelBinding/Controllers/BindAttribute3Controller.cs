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
	public sealed class BindAttribute3Controller : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult EditChild()
		{
			ViewResult											Result=View("EditChildBind");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult EditChildCallback(CChildBind ChildBind)
		{
			ViewResult											Result=View("ViewChildBind",ChildBind);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------