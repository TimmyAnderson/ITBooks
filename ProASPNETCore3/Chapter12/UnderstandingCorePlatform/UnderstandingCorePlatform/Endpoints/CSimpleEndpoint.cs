using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CSimpleEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			string												Content=$"SIMPLE ENDPOINT is CALLED for URL [{Context.Request.Path}] !";

			await Context.Response.WriteAsync(Content);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------