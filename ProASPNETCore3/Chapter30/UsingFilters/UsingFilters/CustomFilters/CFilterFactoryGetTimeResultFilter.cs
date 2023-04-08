using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
using UsingFilters.Services;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! FILTER zobrazi cas, ktory bol namerany SERVICE [ITimeService].
	// !!!!! Kedze FILTER vyuziva DEPENDENCY INJECTION, tak NIE JE implementovany ako ATTRIBUTE.
	public sealed class CFilterFactoryGetTimeResultFilter : IResultFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ITimeService							MTimeService;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! PARAMETER naplni DEPENDENCY INJECTION FRAMEWORK.
		// !!!!! SERVICE [ITimeService] ma SCOPED LIFESCOPE a teda je SHARED medzi vsetkymi instanciami FILTER CLASSES pouzitymi pri spracovani jedneho HTTP REQUEST.
		public CFilterFactoryGetTimeResultFilter(ITimeService TimeService)
		{
			MTimeService=TimeService;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnResultExecuting(ResultExecutingContext Context)
		{
			// !!! Kedze SERVICE [ITimeService] ma SCOPED LIFESCOPE, jeho zivotnost trva pocas celeho spracovania HTTP REQUEST.
			// !!!!! Hodnotu PROPERTY [ITimeService.ElapsedTimeInTicks] naplnil FILTER [CDependencyInjectionSetTimeActionFilter], ktory kedze je ACTION FILTER, tak sa vykona VZDY SKOR ako RESULT FILTER.
			long												ElapsedTimeInTicks=MTimeService.ElapsedTimeInTicks;

			ViewResult											Result=(ViewResult) Context.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
			CResultMessageWithExecutionTime						ModifiedModel=new CResultMessageWithExecutionTime(Model.Message,ElapsedTimeInTicks.ToString());

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithExecutionTime";
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