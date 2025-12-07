using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class HttpLoggingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<HttpLoggingController>			MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public HttpLoggingController(ILogger<HttpLoggingController> Logger)
		{
			MLogger=Logger;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("WriteLog")]
		public IActionResult WriteLog()
		{
			MLogger.LogInformation("WRITE LOG - This is LOG.");

			string												Content="LOG WRITTEN.";
			IActionResult										Response=Ok(Content);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("WriteLogs")]
		public IActionResult WriteLogs()
		{
			MLogger.LogInformation("WRITE LOGS - This is LOG 1.");
			MLogger.LogInformation("WRITE LOGS - This is LOG 2.");

			string												Content="LOGS WRITTEN.";
			IActionResult										Response=Ok(Content);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------