﻿using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
//----------------------------------------------------------------------------------------------------------------------
namespace UnderstandingCorePlatform.Middlewares
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class CBranchAMiddleware1
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly RequestDelegate						MNextMiddlewareComponent;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public CBranchAMiddleware1(RequestDelegate NextMiddlewareComponent)
		{
			MNextMiddlewareComponent=NextMiddlewareComponent;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public async Task Invoke(HttpContext Context)
		{
			await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CBranchAMiddleware1)}] is CALLED BEFORE CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.PathBase}] !");

			await MNextMiddlewareComponent.Invoke(Context);

			await Context.Response.WriteAsync($"MIDDLEWARE COMPONENT [{nameof(CBranchAMiddleware1)}] is CALLED AFTER CALLING NEXT MIDDLEWARE COMPONENT for URL [{Context.Request.PathBase}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------