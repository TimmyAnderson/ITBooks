using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using AdvancedControllersAndViews.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class EncodingController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowHtmlEncodings()
		{
			CStringValue										Model=new CStringValue("<b><i>This is some STRING !</i></b>");
			IActionResult										Result=View("UseHtmlEncoding",Model);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowJsonEncodings()
		{
			CName												Model=new CName(0,"Timothy","Anderson",12,ESex.Male);
			IActionResult										Result=View("UseJsonEncoding",Model);
			
			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------