using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace WebAPICommonPracticesWeb
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class SynchronousVsAsynchronousController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("SynchronousMethod")]
		public string SynchronousMethod()
		{
			string												Content=System.IO.File.ReadAllText("Files\\MyTextFile.txt");
			string												Result=$"SYNCHRONOUS RESULT [{Content}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("AsynchronousMethod")]
		public async Task<string> AsynchronousMethod()
		{
			string												Content=await System.IO.File.ReadAllTextAsync("Files\\MyTextFile.txt");
			string												Result=$"ASYNCHRONOUS RESULT [{Content}].";

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------