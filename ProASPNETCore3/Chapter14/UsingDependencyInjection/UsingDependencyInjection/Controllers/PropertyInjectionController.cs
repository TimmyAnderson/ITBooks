using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingDependencyInjection.Model;
//-----------------------------------------------------------------------------
namespace UsingDependencyInjection.Controllers
{
//-----------------------------------------------------------------------------
	public sealed class PropertyInjectionController
	{
//-----------------------------------------------------------------------------
		private ControllerContext								MContext;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		// !!!!! Ak je PROPERTY TYPE [ControllerContext] oznacena pomocou ATTRIBUTE [ControllerContextAttribute], tak ASP.NET pomocou PROPERTY DEPENDENCY INJECTION ju AUTOMATICKY naplni instanciu CLASS [ControllerContext], ktora obsahuje CONTEXT DATA akutalneho HTTP REQUEST.
		[ControllerContext]
		public ControllerContext								Context
		{
			get
			{
				return(MContext);
			}
			set
			{
				MContext=value;
			}
		}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
		// !!! ACTION METHOD pouziva CONTEXT DATA, ktore CONTROLLER ziskal pomocou PROPERTY oznacenej ATTRIBUTE [ControllerContextAttribute].
		public ViewResult MyActionMethod()
		{
			Dictionary<string,string>							Data=new Dictionary<string,string>();
			
			// !!! Pomocou PROPERTY [Request] je mozne pristupit k OBJECT TYPE [HttpRequest].
			Data.Add("Request.Query",MContext.HttpContext.Request.Query.ToString());
			Data.Add("Request.Headers.Count",MContext.HttpContext.Request.Headers.Count.ToString());
			Data.Add("Request.Body.CanRead",MContext.HttpContext.Request.Body.CanRead.ToString());

			// !!! Pomocou PROPERTY [Response] je mozne pristupit k OBJECT TYPE [HttpResponse].
			Data.Add("Response.ContentType",MContext.HttpContext.Response.ContentType);
			Data.Add("Response.StatusCode",MContext.HttpContext.Response.StatusCode.ToString());

			CResultData											ViewModel=new CResultData(Data);
			ViewDataDictionary									DataDictionary=new ViewDataDictionary(new EmptyModelMetadataProvider(),new ModelStateDictionary());

			DataDictionary.Model=ViewModel;

			ViewResult											Result=new ViewResult();

			Result.ViewName="ResultData";
			Result.ViewData=DataDictionary;

			return(Result);
		}
//-----------------------------------------------------------------------------
	}
//-----------------------------------------------------------------------------
}
//-----------------------------------------------------------------------------