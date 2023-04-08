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
	// CLASS implementuje SYNCHRONOUS VERSION RESOURCE FILTER.
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CSynchronousResourceAttribute : Attribute, IResourceFilter
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly Dictionary<PathString,IActionResult>	MCache;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSynchronousResourceAttribute()
		{
			MCache=new Dictionary<PathString,IActionResult>();
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public void OnResourceExecuting(ResourceExecutingContext Context)
		{
			Console.WriteLine("++++++++++ METHOD [OnResourceExecuting()] ! ++++++++++");

			IActionResult										CachedResult;

			if (MCache.TryGetValue(Context.HttpContext.Request.Path,out CachedResult)==true)
			{
				// !!! RESULT sa odstrani z CACHE.
				MCache.Remove(Context.HttpContext.Request.Path);

				// !!! Vykona sa SHORTCUT, ked sa vrati CACHED RESULT.
				Context.Result=CachedResult;
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		public void OnResourceExecuted(ResourceExecutedContext Context)
		{
			// !!!!! RESOURCE FILTER NEMOZE zmenit hodnotu RESULT nastavenim PROPERTY [ResourceExecutedContext.Result], pretoze HTTP RESPONSE MESSAGE uz bola vygenerovana. No moze si ulozit hodnotu RESULT a pouzit ju pre dalsie HTTP REQUEST MESSAGES pri implementacii CACHING.

			// !!! RESULT sa ulozi do CACHE.
			MCache.Add(Context.HttpContext.Request.Path,Context.Result);

			Console.WriteLine("++++++++++ METHOD [OnResourceExecuted()] ! ++++++++++");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------