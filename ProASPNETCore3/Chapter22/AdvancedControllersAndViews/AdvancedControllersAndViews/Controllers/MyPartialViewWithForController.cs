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
	public class MyPartialViewWithForController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowNames1()
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Timmy","Anderson",12,ESex.Male));
			Names.Add(new CName(2,"Jenny","Thompson",13,ESex.Female));

			CNamesWithHeader									Model=new CNamesWithHeader("TIMMY FIRST !",Names.ToArray());
			ViewResult											Result=View("ViewUsingPartialViewsWithFor",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult ShowNames2()
		{
			List<CName>											Names=new List<CName>();

			Names.Add(new CName(1,"Jenny","Thompson",13,ESex.Female));
			Names.Add(new CName(2,"Timmy","Anderson",12,ESex.Male));

			CNamesWithHeader									Model=new CNamesWithHeader("JENNY FIRST !",Names.ToArray());
			ViewResult											Result=View("ViewUsingPartialViewsWithFor",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------