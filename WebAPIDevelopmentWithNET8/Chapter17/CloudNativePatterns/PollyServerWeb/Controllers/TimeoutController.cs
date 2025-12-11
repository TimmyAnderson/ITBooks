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
	public class TimeoutController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(SlowMethod))]
		public async Task<IActionResult> SlowMethod(string ID, int TimeoutInMS)
		{
			Console.WriteLine($"SLOW METHOD STARTED. ID [{ID}].");

			await Task.Delay(TimeoutInMS);
			
			string												Content=$"METHOD FINISHED. ID [{ID}].";
			IActionResult										Result=Ok(Content);

			Console.WriteLine($"SLOW METHOD FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------