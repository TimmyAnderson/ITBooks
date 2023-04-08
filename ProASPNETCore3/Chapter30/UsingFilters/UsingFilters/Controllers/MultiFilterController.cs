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
	public sealed class MultiFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousMultiFilter(false,false)]
		public ViewResult SynchronousNoException()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousMultiFilter(false,false)]
		public ViewResult SynchronousException()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousMultiFilter(true,false)]
		public ViewResult SynchronousExceptionWithHandlingInActionFilter()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CSynchronousMultiFilter(false,true)]
		public ViewResult SynchronousExceptionWithHandlingInExceptionFilter()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousMultiFilter(false,false)]
		public ViewResult AsynchronousNoException()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousMultiFilter(false,false)]
		public ViewResult AsynchronousException()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousMultiFilter(true,false)]
		public ViewResult AsynchronousExceptionWithHandlingInActionFilter()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
		[CAsynchronousMultiFilter(false,true)]
		public ViewResult AsynchronousExceptionWithHandlingInExceptionFilter()
		{
			throw(new InvalidOperationException("This is SOME EXCEPTION !"));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------