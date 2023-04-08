using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using SimpleWebApplication.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace SimpleWebApplication.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class HomeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult Index()
		{
			IActionResult										Result=View("Index");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet]
		public IActionResult RsvpForm()
		{
			IActionResult										Result=View("RsvpForm");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpPost]
		public IActionResult RsvpForm(CGuestResponse GuestResponse)
		{
			if (ModelState.IsValid==true)
			{
				CRepository.AddResponse(GuestResponse);

				IActionResult									Result=View("Thanks",GuestResponse);

				return(Result);
			}
			else
			{
				// !!! V pripade ERROR sa zobrazi VIEW s ERRORS.
				IActionResult									Result=View("RsvpForm");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ListResponses()
		{
			IEnumerable<CGuestResponse>							Model=CRepository.Responses.Where(P => P.WillAttend==true);
			IActionResult										Result=View("ListResponses",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------