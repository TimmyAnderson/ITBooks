using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// CLASS implementuje SYNCHRONOUS VERSION EXCEPTION FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousExceptionAttribute : Attribute, IExceptionFilter
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
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------