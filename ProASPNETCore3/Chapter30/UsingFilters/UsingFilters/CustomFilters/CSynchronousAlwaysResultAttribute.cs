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
	// CLASS implementuje SYNCHRONOUS VERSION ALWAYS RESULT FILTER. CLASS zaroven implementuje aj EXCEPTION FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousAlwaysResultAttribute : Attribute, IExceptionFilter, IAlwaysRunResultFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		public void OnException(ExceptionContext Context)
		{
			Dictionary<string,string>							Data=new Dictionary<string,string>();

			Data.Add("Exception Type",Context.Exception.GetType().ToString());
			Data.Add("Exception Message",Context.Exception.Message);

			CResultData											Model=new CResultData(Data);

			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=Model;

			ViewResult											ModifiedResult=new ViewResult();

			ModifiedResult.ViewName="ResultData";
			ModifiedResult.ViewData=DataDictionary;

			Context.Result=ModifiedResult;

			// !!! IBA ak je EXCEPTION HANDLED, tak je volany RESULT FILTER.
			Context.ExceptionHandled=true;
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! METHOD je volana AZ po vykonani ACTION METHOD, ale PRED vygenerovanim HTTP RESPONSE.
		public void OnResultExecuting(ResultExecutingContext Context)
		{
			ViewResult											Result=(ViewResult) Context.Result;

			if ((Result.Model is CResultMessage)==true)
			{
				CResultMessage									Model=(CResultMessage) Result.Model;
				CResultMessageWithTime							ModifiedModel=new CResultMessageWithTime(Model.Message,DateTime.Now.ToString());

				ViewDataDictionary								DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

				DataDictionary.Model=ModifiedModel;

				ViewResult										ModifiedResult=new ViewResult();

				ModifiedResult.ViewName="ResultMessageWithTime";
				ModifiedResult.ViewData=DataDictionary;

				Context.Result=ModifiedResult;
			}
			else if ((Result.Model is CResultData)==true)
			{
				CResultData										Model=(CResultData) Result.Model;
				string											ExceptionType=Model.Data["Exception Type"];
				string											ExceptionMessage=Model.Data["Exception Message"];
				CResultMessageWithTime							ModifiedModel=new CResultMessageWithTime($"EXCEPTION TYPE [{ExceptionType}] EXCEPTION MESSAGE [{ExceptionMessage}] !",DateTime.Now.ToString());

				ViewDataDictionary								DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

				DataDictionary.Model=ModifiedModel;

				ViewResult										ModifiedResult=new ViewResult();

				ModifiedResult.ViewName="ResultMessageWithTime";
				ModifiedResult.ViewData=DataDictionary;

				Context.Result=ModifiedResult;
			}
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