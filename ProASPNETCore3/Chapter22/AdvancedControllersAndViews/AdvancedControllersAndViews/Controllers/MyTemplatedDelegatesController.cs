using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using AdvancedControllersAndViews.Models;
//----------------------------------------------------------------------------------------------------------------------
namespace AdvancedControllersAndViews.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public class MyTemplatedDelegatesController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowName()
		{
			CName												Model=new CName(0,"Timmy","Anderson",12,ESex.Male);
			ViewResult											Result=View("UseTemplatedDelegates",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------