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
	public sealed class CSimpleMiddleware3
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddleware;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleMiddleware3(RequestDelegate NextMiddleware)
		{
			MNextMiddleware=NextMiddleware;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!!!! DEPENDENCY INJECTION je mozne aplikovat aj na PARAMETERS METHODS, ktore vola ASP.NET CORE, ako je naopriklad ENDPOINT INTERFACE METHOD.
		public async Task Invoke(HttpContext Context, ITextService4 TextService4)
		{
			if (Context.Request.Path=="/EndpointMiddleware4")
			{
				await Context.Response.WriteAsync($"MESSAGE form SERVICE [{TextService4.GetText()}] !");
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