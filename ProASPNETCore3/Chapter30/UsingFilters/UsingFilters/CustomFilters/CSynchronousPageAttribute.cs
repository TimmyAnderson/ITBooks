using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
using UsingFilters.Pages;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// CLASS implementuje SYNCHRONOUS VERSION PAGE FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousPageAttribute : Attribute, IPageFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private Stopwatch										MStopwatch;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSynchronousPageAttribute()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnPageHandlerSelected(PageHandlerSelectedContext Context)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnPageHandlerExecuting(PageHandlerExecutingContext Context)
		{
			MStopwatch=new Stopwatch();

			MStopwatch.Start();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnPageHandlerExecuted(PageHandlerExecutedContext Context)
		{
			MStopwatch.Stop();

			PageResult											Result=(PageResult) Context.Result;
			PageApplyPageFilterSynchronousModel					Model=(PageApplyPageFilterSynchronousModel) Result.Model;
			CResultMessageWithExecutionTime						ModifiedModel=new CResultMessageWithExecutionTime(Model.Message,MStopwatch.ElapsedTicks.ToString());

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithExecutionTime";
			ModifiedResult.ViewData=DataDictionary;

			Context.Result=ModifiedResult;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------