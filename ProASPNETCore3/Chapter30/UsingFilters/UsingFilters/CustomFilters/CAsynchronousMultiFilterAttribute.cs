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
	public class CAsynchronousMultiFilterAttribute : Attribute, IAsyncAuthorizationFilter, IAsyncActionFilter, IAsyncResultFilter, IAsyncExceptionFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly bool									MProcessExceptionInActionFilter;
		private readonly bool									MProcessExceptionInExceptionFilter;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAsynchronousMultiFilterAttribute(bool ProcessExceptionInActionFilter, bool ProcessExceptionInExceptionFilter)
		{
			MProcessExceptionInActionFilter=ProcessExceptionInActionFilter;
			MProcessExceptionInExceptionFilter=ProcessExceptionInExceptionFilter;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public Task OnAuthorizationAsync(AuthorizationFilterContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnAuthorizationAsync()] ! ++++++++++");

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task OnActionExecutionAsync(ActionExecutingContext Context, ActionExecutionDelegate Next)
		{
			Console.WriteLine("++++++++++ METHOD [OnActionExecutionAsync()] CALLED before CALLING NEXT DELEGATE ! ++++++++++");

			ActionExecutedContext								ExecutedContext=await Next();

			Console.WriteLine("++++++++++ METHOD [OnActionExecutionAsync()] CALLED after CALLING NEXT DELEGATE ! ++++++++++");

			if (ExecutedContext.Exception!=null)
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
					ExecutedContext.Result=Result;

					// !!! Nastavi sa, ze EXCEPTION je HANDLED.
					ExecutedContext.ExceptionHandled=true;

					Console.WriteLine("++++++++++ EXCEPTION was HANDLED in ACTION METHOD ! ++++++++++");
				}
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task OnResultExecutionAsync(ResultExecutingContext Context, ResultExecutionDelegate Next)
		{
			Console.WriteLine("++++++++++ METHOD [OnResultExecutionAsync()] CALLED before CALLING NEXT DELEGATE ! ++++++++++");

			await Next();

			Console.WriteLine("++++++++++ METHOD [OnResultExecutionAsync()] CALLED after CALLING NEXT DELEGATE ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
		public Task OnExceptionAsync(ExceptionContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnExceptionAsync()] ! ++++++++++");

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

			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------