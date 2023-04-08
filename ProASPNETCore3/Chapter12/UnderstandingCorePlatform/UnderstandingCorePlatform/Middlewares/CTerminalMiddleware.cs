using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! TERMINAL MIDDLEWARE COMPONENT je volana pre kazdu HTTP REQUEST MESSAGE, ktora nebola spracovana inym MIDDLEWARE COMPONENT.
	public static class CTerminalMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task MiddlewareCallback(HttpContext Context)
		{
			if (Context.Request.Path=="/TerminalMiddleware")
			{
				await Context.Response.WriteAsync($"TERMINAL MIDDLEWARE COMPONENT [{nameof(CTerminalMiddleware)}] is CALLED for URL [{Context.Request.Path}] !");
			}

			// !!!!! TERMINAL MIDDLEWARE COMPONENT NESMIE volat nasledujucu MIDDLEWARE COMPONENT v REQUEST PIPELINE, pretoze ziadna nasledujuca MIDDLEWARE COMPONENT v REQUEST PIPELINE sa za TERMINAL MIDDLEWARE COMPONENT NENACHADZA.
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------