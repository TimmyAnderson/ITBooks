using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using ViewComponents.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace ViewComponents.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class ParametersViewComponentsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInPlainTextUsingInvoke()
		{
			ETextType											Model=ETextType.E_PLAIN_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingInvoke",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInBoldTextUsingInvoke()
		{
			ETextType											Model=ETextType.E_BOLD_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingInvoke",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInItalicsTextUsingInvoke()
		{
			ETextType											Model=ETextType.E_ITALICS_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingInvoke",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInPlainTextUsingTagHelper()
		{
			ETextType											Model=ETextType.E_PLAIN_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingTagHelper",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInBoldTextUsingTagHelper()
		{
			ETextType											Model=ETextType.E_BOLD_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingTagHelper",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ActionMethodNamesInItalicsTextUsingTagHelper()
		{
			ETextType											Model=ETextType.E_ITALICS_TEXT;
			ViewResult											Result=View("ShowNamesViewUsingTagHelper",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------