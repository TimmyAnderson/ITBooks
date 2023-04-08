using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.TagHelpers;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseSelectTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly IChildProvider							MChildProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public UseSelectTagHelpersController(IChildProvider ChildProvider)
		{
			MChildProvider=ChildProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseSelectAttributes()
		{
			ViewResult											Result=View("UseSelectAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseSelectAttributesCallback(CChild Child)
		{
			MChildProvider.AddChild(Child);

			CChild[]											Model=MChildProvider.GetChildren();
			IActionResult										Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseSelectWithItemsFromEnum()
		{
			ViewResult											Result=View("UseSelectWithItemsFromEnum");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseSelectWithItemsFromEnumCallback(CChild Child)
		{
			MChildProvider.AddChild(Child);

			CChild[]											Model=MChildProvider.GetChildren();
			IActionResult										Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseSelectWithItemsFromEnumFromViewBag()
		{
			// !!! Do VIEW BAG sa ulozia vsetky ITEMS z ENUM 'ESex'.
			ViewBag.Sexes=new SelectList(Enum.GetValues(typeof(ESex)));

			ViewResult											Result=View("UseSelectWithItemsFromEnumFromViewBag");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseSelectWithItemsFromEnumFromViewBagCallback(CChild Child)
		{
			MChildProvider.AddChild(Child);

			CChild[]											Model=MChildProvider.GetChildren();
			IActionResult										Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseSelectWithItemsFromEnumUsingCustomTagHelper()
		{
			ViewResult											Result=View("UseSelectWithItemsFromEnumUsingCustomTagHelper");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseSelectWithItemsFromEnumUsingCustomTagHelperCallback(CChild Child)
		{
			MChildProvider.AddChild(Child);

			CChild[]											Model=MChildProvider.GetChildren();
			IActionResult										Result=View("ViewChildren",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------