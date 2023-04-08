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
	// CLASS implementuje ASYNCHRONOUS VERSION RESULT FILTER.
	// !!! ATTRIBUTE umoznuje viacnasobnu aplikaciu.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=true)]
	public sealed class CAsynchronousResultInstanceLifetimeAttribute : Attribute, IAsyncResultFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Guid									MGuid;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAsynchronousResultInstanceLifetimeAttribute()
		{
			MGuid=Guid.NewGuid();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD je volana AZ po vykonani ACTION METHOD, ale PRED vygenerovanim HTTP RESPONSE.
		public async Task OnResultExecutionAsync(ResultExecutingContext Context, ResultExecutionDelegate Next)
		{
			ViewResult											Result=(ViewResult) Context.Result;
			CResultMessage										Model=(CResultMessage) Result.Model;
			string												NewMessage=$"{Model.Message} CONTENT ADDED by RESULT FILTER with GUID [{MGuid}] !";
			CResultMessage										ModifiedModel=new CResultMessage(NewMessage);

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ModifiedModel;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultMessage";
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