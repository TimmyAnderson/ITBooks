using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Extensions;
using UsingUrlRouting.Helpers;
using UsingUrlRouting.Model;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public class CReturnPlainTextEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task ProcessEndpointRequest(HttpContext Context)
		{
			Context.Response.StatusCode=200;
			Context.Response.ContentType="text/plain";

			await Context.Response.WriteAsync($"Hello from ENPOINT [{nameof(CReturnPlainTextEndpoint)}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------