using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CBranchCEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			string												Content=$"ENDPOINT [{nameof(CBranchCEndpoint)}] is CALLED for URL [{Context.Request.Path}] !";

			await Context.Response.WriteAsync(Content);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------