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
	// CLASS implementuje SYNCHRONOUS VERSION RESULT FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousResultAttribute : Attribute, IResultFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD je volana AZ po vykonani ACTION METHOD, ale PRED vygenerovanim HTTP RESPONSE.
		public void OnResultExecuting(ResultExecutingContext Context)
		{
			ViewResult											Result=(ViewResult) Context.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
			CResultMessageWithTime								ModifiedModel=new CResultMessageWithTime(Model.Message,DateTime.Now.ToString());

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessageWithTime";
			ModifiedResult.ViewData=DataDictionary;

			Context.Result=ModifiedResult;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD je volana AZ po vykonani ACTION METHOD, a AZ po vygenerovani HTTP RESPONSE.
		public void OnResultExecuted(ResultExecutedContext Context)
		{
			Console.WriteLine($"CANCELLED [{Context.Canceled}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------