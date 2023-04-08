using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Extensions;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Midlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public class CTerminalMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task ProcessEndpointRequest(HttpContext Context, Func<Task> Next)
		{
			await Context.Response.WriteAsync($"TERMINAL ENDPOINT REACHED for URL [{Context.Request.GetDisplayUrl()}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------