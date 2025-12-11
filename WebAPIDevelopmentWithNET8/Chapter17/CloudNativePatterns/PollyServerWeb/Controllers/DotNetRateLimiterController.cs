using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.RateLimiting;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyServerWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class DotNetRateLimiterController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Aplikuje sa RATE LIMITER.
		[EnableRateLimiting(Program.RATE_LIMTER_POLICY_NAME)]
		[HttpGet(nameof(MyMethod))]
		public IActionResult MyMethod(string ID)
		{
			Console.WriteLine($"MY METHOD STARTED. ID [{ID}].");

			string												Content=$"MY METHOD FINISHED. ID [{ID}].";
			IActionResult										Result=Ok(Content);

			Console.WriteLine($"MY METHOD FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------