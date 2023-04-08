﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.Controllers
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class ControllerActionFilterController : Controller
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! ACTION FILTER je implementovany priamo na urovni CONTROLLER.
		public async override Task OnActionExecutionAsync(ActionExecutingContext Context, ActionExecutionDelegate Next)
		{
			Stopwatch											Stopwatch=new Stopwatch();

			Stopwatch.Start();

			// !!! Explicitne sa vola sa ACTION METHOD.
			ActionExecutedContext								ExecutedContext=await Next();

			Stopwatch.Stop();

			ViewResult											Result=(ViewResult) ExecutedContext.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public ViewResult MyActionMethod()
		{
			CResultMessage										Model=new CResultMessage("ACTION METHOD is EXECUTED !");
			ViewResult											Result=View("ResultMessage",Model);

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------