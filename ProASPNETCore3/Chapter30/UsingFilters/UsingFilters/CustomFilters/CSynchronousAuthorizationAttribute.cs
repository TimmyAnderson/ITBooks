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
	// CLASS implementuje SYNCHRONOUS VERSION AUTHORIZATION FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousAuthorizationAttribute : Attribute, IAuthorizationFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		public void OnAuthorization(AuthorizationFilterContext Context)
		{
			if (Context.HttpContext.Request.IsHttps==false)
			{
				// !!! PROPERTY [AuthorizationFilterContext.Result] sa nastavi IBA ak je HTTP REQUEST je UNAUTHORIZED.

				string											ActionMethodName=Context.ActionDescriptor.DisplayName;
				CResultMessage									ViewModel=new CResultMessage(ActionMethodName);
				ViewDataDictionary								DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

				DataDictionary.Model=ViewModel;

				ViewResult										Result=new ViewResult();

				Result.ViewName="Unauthorized";
				Result.ViewData=DataDictionary;

				Context.Result=Result;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------