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
	public class MyPartialViewController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowNames1()
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Timmy","Anderson",12,ESex.Male));
			Names.Add(new CName(2,"Jenny","Thompson",13,ESex.Female));

			CName[]												Model=Names.ToArray();
			ViewResult											Result=View("ViewUsingPartialViews",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowNames2()
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Jenny","Thompson",13,ESex.Female));
			Names.Add(new CName(2,"Timmy","Anderson",12,ESex.Male));

			CName[]												Model=Names.ToArray();
			ViewResult											Result=View("ViewUsingPartialViews",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------