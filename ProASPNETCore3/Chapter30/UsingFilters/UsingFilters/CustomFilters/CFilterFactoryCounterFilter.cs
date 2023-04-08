using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Services;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FILTER je vytvarny DEPENDENCY INJECTION FRAMEWORK ako SINGLETON OBJECT.
	public sealed class CFilterFactoryCounterFilter : IActionFilter, IResultFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Kedze FILTER je SINGLETON, SERVICE [ICounterService] MUSI byt THREAD SAFE.
		private readonly ICounterService						MCounterService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CFilterFactoryCounterFilter(ICounterService CounterService)
		{
			MCounterService=CounterService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuting(ActionExecutingContext Context)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnActionExecuted(ActionExecutedContext Context)
		{
			// !!! Inkrementuje sa hodnota COUNTER v THREAD SAFE SINGLETON SERVICE.
			MCounterService.IncrementCounter();
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnResultExecuting(ResultExecutingContext Context)
		{
			// !!! Nacita sa hodnota COUNTER z THREAD SAFE SINGLETON SERVICE.
			int													Counter=MCounterService.Counter;

			ViewResult											Result=(ViewResult) Context.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
			CResultMessageWithCounter							ModifiedModel=new CResultMessageWithCounter(Model.Message,Counter);

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithCounter";
			ModifiedResult.ViewData=DataDictionary;

			Context.Result=ModifiedResult;
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnResultExecuted(ResultExecutedContext Context)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------