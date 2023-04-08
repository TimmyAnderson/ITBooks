using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSimpleMiddleware2
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddleware;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleMiddleware2(RequestDelegate NextMiddleware)
		{
			MNextMiddleware=NextMiddleware;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task Invoke(HttpContext Context)
		{
			if (Context.Request.Path=="/EndpointMiddleware3")
			{
				// !!! DEPENDENCY INJECTION je mozne pouzit aj pomocou volania METHODS INTERFACE [IServiceProvider].
				ITextService3									TextService3=Context.RequestServices.GetRequiredService<ITextService3>();

				await Context.Response.WriteAsync($"MESSAGE form SERVICE [{TextService3.GetText()}] !");
			}
			else
			{
				await MNextMiddleware(Context);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------