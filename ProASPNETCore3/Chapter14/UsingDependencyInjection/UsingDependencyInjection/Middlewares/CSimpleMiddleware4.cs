using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using UsingDependencyInjection.Helpers;
using UsingDependencyInjection.Service;
//----------------------------------------------------------------------------------------------------------------------
namespace UsingDependencyInjection.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CSimpleMiddleware4
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddleware;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CSimpleMiddleware4(RequestDelegate NextMiddleware)
		{
			MNextMiddleware=NextMiddleware;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task Invoke(HttpContext Context)
		{
			if (Context.Request.Path=="/EndpointMiddleware5")
			{
				// !!! CLASS 'CUsing3Services' pouziva v CONSTRUCTOR SERVICES, ktore su naplnene pomocou DEPENDENCY INJECTION. Preto je nutne na vytvorenie instancie tejto CLASS pouzit METHOD CLASS [ActivatorUtilities].
				CUsing3Services									Using3Services=ActivatorUtilities.CreateInstance<CUsing3Services>(Context.RequestServices);

				await Context.Response.WriteAsync($"MESSAGE form SERVICE 1 [{Using3Services.GetText1()}] !");
				await Context.Response.WriteAsync($" ");
				await Context.Response.WriteAsync($"MESSAGE form SERVICE 2 [{Using3Services.GetText2()}] !");
				await Context.Response.WriteAsync($" ");
				await Context.Response.WriteAsync($"MESSAGE form SERVICE 3 [{Using3Services.GetText3()}] !");
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