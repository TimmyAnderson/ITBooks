using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ASPCoreFundamentals2.LogCategories;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.Timeouts;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.RateLimiting;
using Microsoft.Extensions.Logging;
using MyNamespace;
using MyNamespace.MySubNamespace;
//----------------------------------------------------------------------------------------------------------------------
namespace ASPCoreFundamentals2
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class StandardMiddlewareComponentsController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static int										MCounter=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("RateLimitedEndpoint")]
		// !!! Na ENDPOINT sa aplikuje RATE LIMITER POLICY.
		[EnableRateLimiting(Program.MY_RATE_LIMITER_POLICY)]
		public string RateLimitedEndpoint()
		{
			int													Counter;

			lock(MLock)
			{
				Counter=++MCounter;
			}

			return($"REQUEST NUMBER [{Counter}] !");
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("RequestTimeoutsEndpoint1")]
		// !!! Aplikuje sa TIMEOUT.
		// !!!!! STANDARD MIDDLEWARE COMPONENT [RequestTimeouts] sa aplikuje IBA ak PROGRAM NEBEZI v DEBUG MODE. V DEBUG MODE je tento MIDDLEWARE COMPONENT VYPNUTY.
		[RequestTimeout(3000)]
		public async Task<ActionResult> RequestTimeoutsEndpoint1(int TimeoutInMS)
		{
			string												MethodName=nameof(RequestTimeoutsEndpoint1);

			try
			{
				// !!! Caka sa na skoncenie TIMEOUT. Ak dojde k prekroceniu MAXIMALNEHO TIMEOUT, tak sa generuje EXCEPTION.
				await Task.Delay(TimeSpan.FromMilliseconds(TimeoutInMS),Request.HttpContext.RequestAborted);

				OkObjectResult									Result=Ok($"ENDPOINT [{MethodName}] COMPLETED SUCCESSFULLY !");

				return(Result);
			}
			catch
			{
				ObjectResult									Result=StatusCode(StatusCodes.Status503ServiceUnavailable,$"ENDPOINT [{MethodName}] FAILED to PROCESS MESSAGE in SPECIFIED TIMEOUT !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("RequestTimeoutsEndpoint2")]
		// !!! Aplikuje sa TIMEOUT pomocou POLICY.
		// !!!!! STANDARD MIDDLEWARE COMPONENT [RequestTimeouts] sa aplikuje IBA ak PROGRAM NEBEZI v DEBUG MODE. V DEBUG MODE je tento MIDDLEWARE COMPONENT VYPNUTY.
		[RequestTimeout(Program.MY_REQUEST_TIMEOUTS_POLICY_1)]
		public async Task<ActionResult> RequestTimeoutsEndpoint2(int TimeoutInMS)
		{
			string												MethodName=nameof(RequestTimeoutsEndpoint2);

			try
			{
				// !!! Caka sa na skoncenie TIMEOUT. Ak dojde k prekroceniu MAXIMALNEHO TIMEOUT, tak sa generuje EXCEPTION.
				await Task.Delay(TimeSpan.FromMilliseconds(TimeoutInMS),Request.HttpContext.RequestAborted);

				OkObjectResult									Result=Ok($"ENDPOINT [{MethodName}] COMPLETED SUCCESSFULLY !");

				return(Result);
			}
			catch
			{
				ObjectResult									Result=StatusCode(StatusCodes.Status503ServiceUnavailable,$"ENDPOINT [{MethodName}] FAILED to PROCESS MESSAGE in SPECIFIED TIMEOUT !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("RequestTimeoutsEndpoint3")]
		// !!! Aplikuje sa TIMEOUT pomocou POLICY.
		// !!!!! STANDARD MIDDLEWARE COMPONENT [RequestTimeouts] sa aplikuje IBA ak PROGRAM NEBEZI v DEBUG MODE. V DEBUG MODE je tento MIDDLEWARE COMPONENT VYPNUTY.
		[RequestTimeout(Program.MY_REQUEST_TIMEOUTS_POLICY_2)]
		public async Task<ActionResult> RequestTimeoutsEndpoint3(int TimeoutInMS)
		{
			string												MethodName=nameof(RequestTimeoutsEndpoint3);
			
			try
			{
				// !!! Caka sa na skoncenie TIMEOUT. Ak dojde k prekroceniu MAXIMALNEHO TIMEOUT, tak sa generuje EXCEPTION.
				await Task.Delay(TimeSpan.FromMilliseconds(TimeoutInMS),Request.HttpContext.RequestAborted);

				OkObjectResult									Result=Ok($"ENDPOINT [{MethodName}] COMPLETED SUCCESSFULLY !");

				return(Result);
			}
			catch
			{
				ObjectResult									Result=StatusCode(StatusCodes.Status503ServiceUnavailable,$"ENDPOINT [{MethodName}] FAILED to PROCESS MESSAGE in SPECIFIED TIMEOUT !");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------