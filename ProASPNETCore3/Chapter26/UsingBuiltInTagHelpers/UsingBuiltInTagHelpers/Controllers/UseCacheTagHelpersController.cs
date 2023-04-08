using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.TagHelpers;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingBuiltInTagHelpers.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class UseCacheTagHelpersController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		private static readonly DateTimeOffset					MAbsoluteExpirationTime=new DateTimeOffset(DateTime.Now+TimeSpan.FromSeconds(60));
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseCacheAttributes()
		{
			ViewBag.AbsoluteExpirationTime=MAbsoluteExpirationTime;

			ViewResult											Result=View("UseCacheAttributes");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		public IActionResult UseCacheVaryByAttribute()
		{
			ViewBag.AbsoluteExpirationTime=MAbsoluteExpirationTime;

			ViewResult											Result=View("UseCacheVaryByAttribute");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------