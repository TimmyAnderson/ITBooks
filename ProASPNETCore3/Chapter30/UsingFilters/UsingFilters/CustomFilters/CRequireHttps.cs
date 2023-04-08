using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingFilters.CustomFilters
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! CUSTOM FILTER vykonavajuci kontrolu ci HTTP REQUEST je zaslany cez HTTPS PROTOCOL dedi z CLASS [RequireHttpsAttribute].
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Method, Inherited=true, AllowMultiple=false)]
	public sealed class CRequireHttps : RequireHttpsAttribute
	{
//----------------------------------------------------------------------------------------------------------------------
		public CRequireHttps()
		{
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected override void HandleNonHttpsRequest(AuthorizationFilterContext FilterContext)
		{
			StatusCodeResult									Result=new StatusCodeResult(403);
			
			FilterContext.Result=Result;
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------