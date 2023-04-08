using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// CLASS implementuje ASYNCHRONOUS VERSION ACTION AND RESULT FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CAsynchronousActionAndResultAttribute : ActionFilterAttribute
	{
//----------------------------------------------------------------------------------------------------------------------
		private long											MExecutionTimeInTicks;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public override async Task OnActionExecutionAsync(ActionExecutingContext Context, ActionExecutionDelegate Next)
		{
			Stopwatch											Stopwatch=new Stopwatch();

			Stopwatch.Start();

			// !!! Explicitne sa vola sa ACTION METHOD.
			await Next();

			Stopwatch.Stop();

			MExecutionTimeInTicks=Stopwatch.ElapsedTicks;
		}
//----------------------------------------------------------------------------------------------------------------------
		public async override Task OnResultExecutionAsync(ResultExecutingContext Context, ResultExecutionDelegate Next)
		{
			ViewResult											Result=(ViewResult) Context.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
			CResultMessageWithExecutionTime						ModifiedModel=new CResultMessageWithExecutionTime(Model.Message,MExecutionTimeInTicks.ToString());

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithExecutionTime";
			ModifiedResult.ViewData=DataDictionary;

			Context.Result=ModifiedResult;

			// !!!!! Volanie METHOD vykona CODE dalsich RESULT FILTERS a nasledne METHOD vola METHOD [Task IActionResult.ExecuteResultAsync(ActionContext Context)], ktora vygeneruje HTTP RESPONSE.
			ResultExecutedContext								ExecutedContext=await Next();

			// !!!!! Tento CODE sa uz vola AZ po VYGENEROVANI HTTP RESPONSE.
			Console.WriteLine($"CANCELLED [{ExecutedContext.Canceled}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------