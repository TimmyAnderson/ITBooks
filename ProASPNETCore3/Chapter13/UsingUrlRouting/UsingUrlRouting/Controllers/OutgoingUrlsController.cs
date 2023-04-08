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
	public sealed class OutgoingUrlsController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly LinkGenerator							MLinkGenerator;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public OutgoingUrlsController(LinkGenerator LinkGenerator)
		{
			MLinkGenerator=LinkGenerator;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult Index()
		{
			// !!! ABSOLUTE URL je generovana z ROUTE, ktora ma NAME 'MyNamedRoute'.
			// !!! 2. PARAMETER je ANONYMOUS TYPE, ktory obsahuje VALUES ROUTE VARIABLES.
			ViewBag.AbsoluteUrlGeneratedByRoute=MLinkGenerator.GetUriByRouteValues("MyNamedRoute",new { FirstName="Timmy", LastName="Anderson" },"http",new HostString("localhost:50000"));

			// !!! RELATIVE URL je generovana z ROUTE, ktora ma NAME 'MyNamedRoute'.
			// !!! 2. PARAMETER je ANONYMOUS TYPE, ktory obsahuje VALUES ROUTE VARIABLES.
			ViewBag.RelativeUrlGeneratedByRoute=MLinkGenerator.GetPathByRouteValues("MyNamedRoute",new { FirstName="Timmy", LastName="Anderson" });
			
			RouteValueDictionary								MyRouteValueDictionary=new RouteValueDictionary();

			MyRouteValueDictionary.Add("FirstName","Jenny");
			MyRouteValueDictionary.Add("LastName","Thompson");

			RouteValuesAddress									MyRouteValuesAddress=new RouteValuesAddress();

			MyRouteValuesAddress.RouteName="MyNamedRoute";

			// !!! ABSOLUTE URL je generovana z ADDRESS, ktora sa odkazuje na NAMED ROUTE 'MyNamedRoute'.
			ViewBag.AbsoluteUrlGeneratedByAddress=MLinkGenerator.GetUriByAddress(MyRouteValuesAddress,MyRouteValueDictionary,"http",new HostString("localhost:50000"));

			// !!! RELATIVE URL je generovana z ADDRESS, ktora sa odkazuje na NAMED ROUTE 'MyNamedRoute'.
			ViewBag.RelativeUrlGeneratedByAddress=MLinkGenerator.GetPathByAddress(HttpContext,MyRouteValuesAddress,MyRouteValueDictionary);
			
			// !!! ABSOLUTE URL je generovana z ENDPOINT NAME.
			ViewBag.AbsoluteUrlGeneratedByEndpointName=MLinkGenerator.GetUriByName("MyEndpointName",new { FirstName="Timmy", LastName="Anderson" },"http",new HostString("localhost:50000"));

			// !!! RELATIVE URL je generovana z ENDPOINT NAME.
			ViewBag.RelativeUrlGeneratedByEndpointName=MLinkGenerator.GetPathByName("MyEndpointName",new { FirstName="Timmy", LastName="Anderson" });

			// !!! ABSOLUTE URL je generovana z CONTROLLER a ACTION METHOD.
			ViewBag.AbsoluteUrlGeneratedByControllerAndActionMethod=MLinkGenerator.GetUriByAction("ProcessName","MyName",new { GivenName="Timmy", FamilyName="Anderson" },"http",new HostString("localhost:50000"));

			// !!! RELATIVE URL je generovana z CONTROLLER a ACTION METHOD.
			ViewBag.RelativeUrlGeneratedByControllerAndActionMethod=MLinkGenerator.GetPathByAction("ProcessName","MyName",new { GivenName="Timmy", FamilyName="Anderson" });

			// !!! ABSOLUTE URL je generovana z PAGE a PAGE HANDLER.
			ViewBag.AbsoluteUrlGeneratedByPageAndPageHandler=MLinkGenerator.GetUriByPage("/PageName","MyHandler",new { GivenName="Timmy", FamilyName="Anderson" },"http",new HostString("localhost:50000"));

			// !!! RELATIVE URL je generovana z PAGE a PAGE HANDLER.
			ViewBag.RelativeUrlGeneratedByPageAndPageHandler=MLinkGenerator.GetPathByPage("/PageName","MyHandler",new { GivenName="Timmy", FamilyName="Anderson" });

			ViewResult											Result=View();

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------