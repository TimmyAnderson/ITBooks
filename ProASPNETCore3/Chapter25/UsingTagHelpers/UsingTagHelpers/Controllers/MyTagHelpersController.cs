using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class MyTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseDivTagHelper()
		{
			ViewResult											Result=View("UseDivTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseAsynchronousDivTagHelper()
		{
			ViewResult											Result=View("UseAsynchronousDivTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScope1TagHelper()
		{
			ViewResult											Result=View("UseScope1TagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScope2TagHelper()
		{
			ViewResult											Result=View("UseScope2TagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScope3TagHelper()
		{
			ViewResult											Result=View("UseScope3TagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseScope4TagHelper()
		{
			ViewResult											Result=View("UseScope4TagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseOrderTagHelper()
		{
			ViewResult											Result=View("UseOrderTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseContentReplacingTagHelper()
		{
			ViewResult											Result=View("UseContentReplacingTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseCustomElementTagHelper()
		{
			ViewResult											Result=View("UseCustomElementTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseElementAndContentModifyingTagHelper()
		{
			ViewResult											Result=View("UseElementAndContentModifyingTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseViewContextTagHelper()
		{
			ViewResult											Result=View("UseViewContextTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseModelExpressionTagHelper()
		{
			CName												Name=new CName(0,"Timmy","Anderson",12);
			ViewResult											Result=View("UseModelExpressionTagHelper",Name);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseCoordinatingTagHelper()
		{
			ViewResult											Result=View("UseCoordinatingTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseSuppressOutputTagHelper()
		{
			ViewResult											Result=View("UseSuppressOutputTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseTagHelperComponent()
		{
			ViewResult											Result=View("UseTagHelperComponent");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseTagHelperComponentTagHelper()
		{
			ViewResult											Result=View("UseTagHelperComponentTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------