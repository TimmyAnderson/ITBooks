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
	public sealed class ResourceFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousResource]
		public ViewResult Synchronous()
		{
			CResultMessageWithTime								Model=new CResultMessageWithTime("ACTION METHOD is EXECUTED !",DateTime.Now.ToString());
			ViewResult											Result=View("ResultMessageChachedSynchronous",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousResource]
		public ViewResult Asynchronous()
		{
			CResultMessageWithTime								Model=new CResultMessageWithTime("ACTION METHOD is EXECUTED !",DateTime.Now.ToString());
			ViewResult											Result=View("ResultMessageChachedAsynchronous",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------