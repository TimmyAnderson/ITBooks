using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using SecuringWebServicesUsingCookies.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace SecuringWebServicesUsingCookies.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class HomeController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult Index()
		{
			return(View());
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------