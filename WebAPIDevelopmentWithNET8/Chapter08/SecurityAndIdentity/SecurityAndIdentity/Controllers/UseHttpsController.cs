using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace SecurityAndIdentity
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class UseHttpsController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("Execute")]
		public string Execute()
		{
			string												Scheme=HttpContext.Request.Scheme;
			string												Host=HttpContext.Request.Host.Value;
			bool												IsHTTPs=HttpContext.Request.IsHttps;
			string												Result=$"SCHEME [{Scheme}] HOST [{Host}] IS HTTPS [{IsHTTPs}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------