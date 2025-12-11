using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace PollyServerWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class RateLimiterController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(MyRateLimterMethod))]
		public IActionResult MyRateLimterMethod(string ID)
		{
			Console.WriteLine($"MY RATE LIMITER METHOD STARTED. ID [{ID}].");

			string												Content=$"MY RATE LIMITER METHOD FINISHED. ID [{ID}].";
			IActionResult										Result=Ok(Content);

			Console.WriteLine($"MY RATE LIMITER METHOD FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------