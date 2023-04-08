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
	public static class CMethodWithConfigurationMiddleware
	{
//----------------------------------------------------------------------------------------------------------------------
		public static async Task MiddlewareCallback(HttpContext Context, Func<Task> NextMiddleware)
		{
			// !!! Ziska sa CONFIGURATION z DEPENDENCY INJECTION FRAMEWORK.
			IOptions<CConfigurationMethodWithConfiguration>		ConfigurationWrapper=(IOptions<CConfigurationMethodWithConfiguration>) Context.RequestServices.GetService(typeof(IOptions<CConfigurationMethodWithConfiguration>));

			// !!! Ziska sa CONFIGURATION CLASS z DEPENDENCY INJECTION FRAMEWORK.
			CConfigurationMethodWithConfiguration				Configuration=ConfigurationWrapper.Value;

			if (Context.Request.Path=="/Endpoint4")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CMethodWithConfigurationMiddleware)}] is CALLED BEFORE CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] ! CONFIGURATION VALUE 1 [{Configuration.Value1}] CONFIGURATION VALUE 2 [{Configuration.Value2}] !");
			}

			await NextMiddleware.Invoke();

			if (Context.Request.Path=="/Endpoint4")
			{
				await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CMethodWithConfigurationMiddleware)}] is CALLED AFTER CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.Path}] ! CONFIGURATION VALUE 1 [{Configuration.Value1}] CONFIGURATION VALUE 2 [{Configuration.Value2}] !");
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------