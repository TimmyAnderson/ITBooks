using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Options;
using UnderstandingCorePlatform.Configurations;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CClassWithConfigurationMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddlewareComponent;
		private readonly IOptions<CConfigurationClassWithConfiguration>	MConfigurationWrapper;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CClassWithConfigurationMiddleware(RequestDelegate NextMiddlewareComponent, IOptions<CConfigurationClassWithConfiguration> ConfigurationWrapper)
		{
			MNextMiddlewareComponent=NextMiddlewareComponent;
			MConfigurationWrapper=ConfigurationWrapper;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task Invoke(HttpContext Context)
		{
			// !!! Ziska sa CONFIGURATION CLASS z DEPENDENCY INJECTION FRAMEWORK.
			CConfigurationClassWithConfiguration				Configuration=MConfigurationWrapper.Value;

			if (Context.Request.Path=="/Endpoint5")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CClassWithConfigurationMiddleware)}] is CALLED BEFORE CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] ! CONFIGURATION VALUE 1 [{Configuration.Value1}] CONFIGURATION VALUE 2 [{Configuration.Value2}] !");
			}

			await MNextMiddlewareComponent.Invoke(Context);

			if (Context.Request.Path=="/Endpoint5")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CClassWithConfigurationMiddleware)}] is CALLED AFTER CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] ! CONFIGURATION VALUE 1 [{Configuration.Value1}] CONFIGURATION VALUE 2 [{Configuration.Value2}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------