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
	public sealed class NameController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[Route("MY_ENDPOINT",Name="MyEndpointName")]
		public ViewResult ProcessName(string FirstName, string LastName)
		{
			ViewBag.FirstName=FirstName;
			ViewBag.LastName=LastName;

			ViewResult											Result=View("ViewName");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------