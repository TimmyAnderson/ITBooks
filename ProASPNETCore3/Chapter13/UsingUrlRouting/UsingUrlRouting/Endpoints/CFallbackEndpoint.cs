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
	public class CFallbackEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task ProcessEndpointRequest(HttpContext Context)
		{
			CResult												Result=new CResult(Context.Request.GetDisplayUrl(),nameof(CFallbackEndpoint));

			await Context.Response.WriteAsync($"----- FALLBACK ENDPOINT REACHED for URL [{Context.Request.GetDisplayUrl()}] ! -----");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------