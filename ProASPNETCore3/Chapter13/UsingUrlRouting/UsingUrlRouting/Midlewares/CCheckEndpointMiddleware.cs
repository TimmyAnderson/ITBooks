using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Extensions;
using UsingUrlRouting.Endpoints;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingUrlRouting.Midlewares
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Tento MIDDLEWARE COMPONENT je aplikovany medzi MIDDLEWARE COMPONENT [EndpointRoutingMiddleware] a MIDDLEWARE COMPONENT [EndpointMiddleware].
	// !!! Kedze MIDDLEWARE COMPONENT je spusteny AZ po vykonani MIDDLEWARE COMPONENT [EndpointMiddleware], tak v pripade, ze sa pre URL nasla prislusna ROUTE, je nastaveny ENDPOINT, ktory sa ma volat v MIDDLEWARE COMPONENT [EndpointMiddleware].
	public class CCheckEndpointMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		public async Task ProcessEndpointRequest(HttpContext Context, Func<Task> Next)
		{
			bool												ExpectedEndpoint=false;

			// !!! Nacita sa ENDPOINT, ktory vybral MIDDLEWARE COMPONENT [EndpointRoutingMiddleware].
			Endpoint											SelectedEndpoint=Context.GetEndpoint();

			// !!! Musi sa vykonat kontrola, lebo nemusela byt najdena ziadna vyhovujuca ROUTE.
			if (SelectedEndpoint!=null)
			{
				object											Target=SelectedEndpoint.RequestDelegate.Target;

				if (Target!=null)
				{
					Type										TargetType=Target.GetType();

					if (TargetType==typeof(CReturnPlainTextEndpoint))
					{
						ExpectedEndpoint=true;
					}
				}
			}

			await Next();

			if (ExpectedEndpoint==true)
			{
				// !!! Prida sa CONTENT do HTTP RESPONSE MESSAGE.
				await Context.Response.WriteAsync($" CONTENT added by MIDDLEWARE COMPONENT [{nameof(CCheckEndpointMiddleware)}] after CALLING ENDPOINT !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------