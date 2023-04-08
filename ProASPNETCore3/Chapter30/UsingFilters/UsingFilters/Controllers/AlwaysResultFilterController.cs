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
	public sealed class AlwaysResultFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousAlwaysResult]
		public ViewResult SynchronousNoException()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousAlwaysResult]
		public ViewResult AsynchronousNoException()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousAlwaysResult]
		public ViewResult SynchronousWithException()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousAlwaysResult]
		public ViewResult AsynchronousWithException()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------