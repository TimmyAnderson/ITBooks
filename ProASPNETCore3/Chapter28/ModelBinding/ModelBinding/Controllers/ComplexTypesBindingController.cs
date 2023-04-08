using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ModelBinding.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ModelBinding.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ComplexTypesBindingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ComplexTypesBindingController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult AddName()
		{
			ViewResult											Result=View("EditChild");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! Z FORM DATA su nacitane PROPERTIES COMPLEX TYPE 'CChild'.
		// !!!!! Kedze COMPLEX TYPE 'CChild' obsahuje COMPLEX TYPE 'CChildAddress', tak MODEL BINDING z FORM DATA nacita aj hodnoty PROPERTIES tohto OBJECT.
		[HttpPost]
		public IActionResult EditChildCallback(CChild Child)
		{
			MChildProvider.AddChild(Child);

			IActionResult										Result=RedirectToAction("ShowNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult ShowNames()
		{
			CChild[]											Model=MChildProvider.GetChildren();
			ViewResult											Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult AddNameWithoutAddress()
		{
			// !!! ADDRESS je UMYSELNE nastaveny na NULL.
			CChild												Child=new CChild(0,"Josh","Hurt",12,ESex.Male,null);

			MChildProvider.AddChild(Child);

			IActionResult										Result=RedirectToAction("ShowNames");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------