using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public static class CMethodMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task MiddlewareCallback(HttpContext Context, Func<Task> NextMiddleware)
		{
			if (Context.Request.Path=="/Endpoint1")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CMethodMiddleware)}] is CALLED BEFORE CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] !");
			}

			// !!! Zavola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE.
			await NextMiddleware.Invoke();

			if (Context.Request.Path=="/Endpoint1")
			{
				// !!! HTTP STATUS CODE a HTTP HEADERS je mozne modifikovat IBA ak nedoslo k zacatiu odosielania HTTP REQUEST MESSAGE HEADERS na CLIENT.
				if (Context.Response.HasStarted==false)
				{
					Context.Response.StatusCode=404;
				}

				// !!!!! Pri pokuse modifikovat HTTP STATUS CODE ci HTTP HEADERS po zacati odosielania HTTP HEADERS na CLIENT, dojde k vzniku EXCEPTION.
				// !!!!! TENTO CODE hodi EXCEPTION.
				//Context.Response.StatusCode=404;

				// !!!!! HTTP RESPONSE MESSAGE BODY vsak JE mozne MODIFIKOVAT aj potom ako boli HTTP RESPONSE MESSAGE HEADERS uz odoslane na CLIENT.
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CMethodMiddleware)}] is CALLED AFTER CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------