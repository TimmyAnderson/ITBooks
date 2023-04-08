using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.Filters;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using UsingFilters.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// CLASS implementuje ASYNCHRONOUS VERSION RESOURCE FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CAsynchronousResourceAttribute : Attribute, IAsyncResourceFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Dictionary<PathString,IActionResult>	MCache;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CAsynchronousResourceAttribute()
		{
			MCache=new Dictionary<PathString,IActionResult>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task OnResourceExecutionAsync(ResourceExecutingContext Context, ResourceExecutionDelegate Next)
		{
			Console.WriteLine("++++++++++ METHOD [OnResultExecutionAsync()] CALLED before CALLING NEXT DELEGATE ! ++++++++++");

			IActionResult										CachedResult;

			if (MCache.TryGetValue(Context.HttpContext.Request.Path,out CachedResult)==true)
			{
				// !!! RESULT sa odstrani z CACHE.
				MCache.Remove(Context.HttpContext.Request.Path);

				// !!! Vykona sa SHORTCUT, ked sa vrati CACHED RESULT.
				Context.Result=CachedResult;

				// !!!!! Kedze sa nastavil RESULT, ktory sposobuje SHORTCUT, NESMIE sa volat DELEGATE [ResourceExecutionDelegate], inak by ASP.NET hodilo EXCEPTION.
				return;
			}

			// !!! Explicitne sa vola sa ACTION METHOD.
			ResourceExecutedContext								ExecutedContext=await Next();

			// !!!!! RESOURCE FILTER NEMOZE zmenit hodnotu RESULT nastavenim PROPERTY [ResourceExecutedContext.Result], pretoze HTTP RESPONSE MESSAGE uz bola vygenerovana. No moze si ulozit hodnotu RESULT a pouzit ju pre dalsie HTTP REQUEST MESSAGES pri implementacii CACHING.

			// !!! RESULT sa ulozi do CACHE.
			MCache.Add(ExecutedContext.HttpContext.Request.Path,ExecutedContext.Result);

			Console.WriteLine($"++++++++++ METHOD [OnResultExecutionAsync()] CALLED after CALLING NEXT DELEGATE ! HTTP RESPONSE CODE is [{ExecutedContext.HttpContext.Response.StatusCode}] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------