using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CUSTOM MIDDLEWARE COMPONENT CLASS MUSI byt THREAD SAFE, pretoze je pouzivana ako SINGLETON.
	public sealed class CClassMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddlewareComponent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! MIDDLEWARE COMPONENT implementovany ako CLASS cez CONSTRUCTOR PARAMETER dostane DELEGATE na nasledujuci MIDDLEWARE COMPONENT.
		public CClassMiddleware(RequestDelegate NextMiddlewareComponent)
		{
			MNextMiddlewareComponent=NextMiddlewareComponent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD implementuje funkcionalitu MIDDLEWARE COMPONENT.
		public async Task Invoke(HttpContext Context)
		{
			if (Context.Request.Path=="/Endpoint2")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CClassMiddleware)}] is CALLED BEFORE CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] !");
			}

			// !!! Zavola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE.
			await MNextMiddlewareComponent.Invoke(Context);

			if (Context.Request.Path=="/Endpoint2")
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
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CClassMiddleware)}] is CALLED AFTER CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------