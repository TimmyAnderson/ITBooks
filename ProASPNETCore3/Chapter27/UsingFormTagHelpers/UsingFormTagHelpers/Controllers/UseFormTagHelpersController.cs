using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.TagHelpers;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseFormTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameProvider							MNameProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public UseFormTagHelpersController(INameProvider NameProvider)
		{
			MNameProvider=NameProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseFormAttributes()
		{
			ViewResult											Result=View("UseFormAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseFormAttributesCallback(CName Name)
		{
			MNameProvider.AddName(Name);

			CName[]												Model=MNameProvider.GetNames();
			IActionResult										Result=View("ViewNames",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseAntiForgery()
		{
			ViewResult											Result=View("UseAntiForgery");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD spracujuca HTTP REQUEST s FORM DATA MUSI byt oznacena ATTRIBUTE [ValidateAntiForgeryTokenAttribute], aby ASP.NET vykonala kontrolu UNIQUE ID.
		[HttpPost]
		[ValidateAntiForgeryToken]
		public IActionResult UseAntiForgeryCallback(CName Name)
		{
			MNameProvider.AddName(Name);

			CName[]												Model=MNameProvider.GetNames();
			IActionResult										Result=View("ViewNames",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------