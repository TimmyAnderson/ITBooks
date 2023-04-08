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
	// CLASS implementuje ASYNCHRONOUS VERSION PAGE FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CAsynchronousPageAttribute : Attribute, IAsyncPageFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		public Task OnPageHandlerSelectionAsync(PageHandlerSelectedContext Context)
		{
			return(Task.CompletedTask);
		}
//----------------------------------------------------------------------------------------------------------------------
		public async Task OnPageHandlerExecutionAsync(PageHandlerExecutingContext Context, PageHandlerExecutionDelegate Next)
		{
			Stopwatch											Stopwatch=new Stopwatch();

			Stopwatch.Start();

			// !!! Explicitne sa vola sa RAZOR PAGE HANDLER.
			PageHandlerExecutedContext							ExecutedContext=await Next();

			Stopwatch.Stop();

			PageResult											Result=(PageResult) ExecutedContext.Result;
			PageApplyPageFilterAsynchronousModel				Model=(PageApplyPageFilterAsynchronousModel) Result.Model;
			CResultMessageWithExecutionTime						ModifiedModel=new CResultMessageWithExecutionTime(Model.Message,Stopwatch.ElapsedTicks.ToString());
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithExecutionTime";
			ModifiedResult.ViewData=DataDictionary;

			// !!! RETURN VALUE DELEGATE sa pouzije na zmenu RESULT.
			ExecutedContext.Result=ModifiedResult;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------