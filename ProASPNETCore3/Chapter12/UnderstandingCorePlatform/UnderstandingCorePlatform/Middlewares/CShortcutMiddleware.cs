using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! SHORTCUT MIDDLEWARE COMPONENT vykona SHORTCUT REQUEST PIPELINE a priamo vygeneruje HTTP RESPONSE MESSAGE.
	public sealed class CShortcutMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddlewareComponent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CShortcutMiddleware(RequestDelegate NextMiddlewareComponent)
		{
			MNextMiddlewareComponent=NextMiddlewareComponent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! METHOD implementuje funkcionalitu MIDDLEWARE COMPONENT.
		public async Task Invoke(HttpContext Context)
		{
			if (Context.Request.Path=="/Endpoint3")
			{
				// !!!!! Vykona sa SHORTCUT, ked sa vygeneruje HTTP RESPONSE MESSAGE no uz sa nezavola MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE.
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CShortcutMiddleware)}] is CALLED for URL [{Context.Request.Path}] !");

				// !!!!! MIDDLEWARE COMPONENT NIZSIE v REQUEST PIPELINE sa NEVOLA.
			}
			else
			{
				// !!! Zavola sa dalsi MIDDLEWARE COMPONENT v REQUEST PIPELINE.
				await MNextMiddlewareComponent.Invoke(Context);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------