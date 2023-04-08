using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingFormTagHelpers.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseTextAreaTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly INameWithNoteProvider					MNameWithNoteProvider;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public UseTextAreaTagHelpersController(INameWithNoteProvider NameWithNoteProvider)
		{
			MNameWithNoteProvider=NameWithNoteProvider;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseTextAreaAttributes()
		{
			ViewResult											Result=View("UseTextAreaAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult UseTextAreaAttributesCallback(CNameWithNote Name)
		{
			MNameWithNoteProvider.AddName(Name);

			CNameWithNote[]										Model=MNameWithNoteProvider.GetNames();
			IActionResult										Result=View("ViewNamesWithNote",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------