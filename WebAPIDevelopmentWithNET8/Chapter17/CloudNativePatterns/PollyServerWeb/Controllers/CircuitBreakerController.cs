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
	public class CircuitBreakerController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private static object									MLock=new object();
		private static int										MCounter=0;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private static int GetAndIncrementCounter()
		{
			lock(MLock)
			{
				return(++MCounter);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(MyCircuitBreakerMethod))]
		public IActionResult MyCircuitBreakerMethod(string ID)
		{
			Console.WriteLine($"MY CIRCUIT BREAKER METHOD STARTED. ID [{ID}].");

			int													Counter=GetAndIncrementCounter();
			IActionResult										Result;

			if ((Counter%4)==1 || (Counter%4)==2)
			{
				Result=StatusCode(451);
			}
			else if ((Counter%4)==3)
			{
				Result=StatusCode(452);
			}
			else
			{
				string											Content=$"TIME [{DateTime.Now}] MY CIRCUIT BREAKER METHOD FINISHED. ID [{ID}].";

				Result=Ok(Content);
			}

			Console.WriteLine($"MY CIRCUIT BREAKER FINISHED. ID [{ID}].");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------