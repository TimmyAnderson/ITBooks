using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Routing;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class MyNameController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult ProcessName(string GivenName, string FamilyName)
		{
			ViewBag.FirstName=GivenName;
			ViewBag.LastName=FamilyName;

			ViewResult											Result=View("ViewName");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------