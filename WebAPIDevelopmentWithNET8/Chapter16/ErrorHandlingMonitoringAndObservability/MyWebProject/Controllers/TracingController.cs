using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.ChangeTracking;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class TracingController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly CMyTypedHttpClient						MTypedHttpClient;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public TracingController(CMyTypedHttpClient TypedHttpClient)
		{
			MTypedHttpClient=TypedHttpClient;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CallServices1")]
		public async Task<IActionResult> CallServices1()
		{
			string												Result1=await MTypedHttpClient.ExecuteMyService1DoSomething1();
			string												Result2=await MTypedHttpClient.ExecuteMyService2DoSomething2();

			string												Content=$"{Result1} {Result2}";

			IActionResult										Response=Ok(Content);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet("CallServices2")]
		public async Task<IActionResult> CallServices2()
		{
			string												Result1=await MTypedHttpClient.ExecuteMyService2DoSomething2();
			string												Result2=await MTypedHttpClient.ExecuteMyService1DoSomething1();

			string												Content=$"{Result1} {Result2}";

			IActionResult										Response=Ok(Content);

			return(Response);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------