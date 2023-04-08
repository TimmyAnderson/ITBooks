using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using UsingFilters.CustomFilters;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ExceptionFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousException]
		public ViewResult Synchronous()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousException]
		public ViewResult Asynchronous()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------