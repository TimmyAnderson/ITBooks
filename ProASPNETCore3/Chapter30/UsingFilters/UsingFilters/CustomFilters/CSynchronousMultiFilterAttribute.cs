using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// CLASS demonstruje poradie volania FILTER METHODS.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public class CSynchronousMultiFilterAttribute : Attribute, IAuthorizationFilter, IActionFilter, IResultFilter, IExceptionFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly bool									MProcessExceptionInActionFilter;
		private readonly bool									MProcessExceptionInExceptionFilter;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSynchronousMultiFilterAttribute(bool ProcessExceptionInActionFilter, bool ProcessExceptionInExceptionFilter)
		{
			MProcessExceptionInActionFilter=ProcessExceptionInActionFilter;
			MProcessExceptionInExceptionFilter=ProcessExceptionInExceptionFilter;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnAuthorization(AuthorizationFilterContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnAuthorization()] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuting(ActionExecutingContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnActionExecuting()] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuted(ActionExecutedContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnActionExecuted()] ! ++++++++++");

			if (Context.Exception!=null)
			{
				if (MProcessExceptionInActionFilter==true)
				{
					CResultMessage								Model=new CResultMessage("EXCEPTION was HANDLED on ACTION FILTER !");
					ViewDataDictionary							DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

					DataDictionary.Model=Model;

					ViewResult									Result=new ViewResult();

					Result.ViewName="ResultMessage";
					Result.ViewData=DataDictionary;

					// !!! Nastavi sa RESULT.
					Context.Result=Result;

					// !!! Nastavi sa, ze EXCEPTION je HANDLED.
					Context.ExceptionHandled=true;

					Console.WriteLine("++++++++++ EXCEPTION was HANDLED in ACTION METHOD ! ++++++++++");
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnResultExecuting(ResultExecutingContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnResultExecuting()] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnResultExecuted(ResultExecutedContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnResultExecuted()] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnException(ExceptionContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnException()] ! ++++++++++");

			if (Context.Exception!=null)
			{
				if (MProcessExceptionInExceptionFilter==true)
				{
					CResultMessage								Model=new CResultMessage("EXCEPTION was HANDLED on EXCEPTION FILTER !");
					ViewDataDictionary							DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

					DataDictionary.Model=Model;

					ViewResult									Result=new ViewResult();

					Result.ViewName="ResultMessage";
					Result.ViewData=DataDictionary;

					// !!! Nastavi sa RESULT.
					Context.Result=Result;

					// !!! Nastavi sa, ze EXCEPTION je HANDLED.
					Context.ExceptionHandled=true;

					Console.WriteLine("++++++++++ EXCEPTION was HANDLED in EXCEPTION METHOD ! ++++++++++");
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------