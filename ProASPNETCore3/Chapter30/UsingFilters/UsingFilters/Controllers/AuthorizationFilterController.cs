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
	public sealed class AuthorizationFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousAuthorization]
		public ViewResult Synchronous()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED via HTTPS !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousAuthorization]
		public ViewResult Asynchronous()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED via HTTPS !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------