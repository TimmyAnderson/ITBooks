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
	public class CConfictingRouteIntEndpoint
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task ProcessEndpointRequest(HttpContext Context)
		{
			Dictionary<string,object>							Data=new Dictionary<string,object>();

			// !!! Vykona sa pristup k ROUTE VARIABLES.
			foreach(KeyValuePair<string,object> Pair in Context.Request.RouteValues)
			{
				Data.Add(Pair.Key,Pair.Value);
			}

			CResult												Result=new CResult(Context.Request.GetDisplayUrl(),nameof(CConfictingRouteIntEndpoint),Data);

			await Context.Response.WriteAsync(CResultsGenerator.ShowResults(Result));
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------