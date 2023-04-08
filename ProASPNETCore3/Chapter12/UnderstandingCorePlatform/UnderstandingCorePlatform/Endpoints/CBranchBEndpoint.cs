using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Endpoints
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CBranchBEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task Endpoint(HttpContext Context)
		{
			string												Content=$"ENDPOINT [{nameof(CBranchBEndpoint)}] is CALLED for URL [{Context.Request.PathBase}] !";

			await Context.Response.WriteAsync(Content);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------