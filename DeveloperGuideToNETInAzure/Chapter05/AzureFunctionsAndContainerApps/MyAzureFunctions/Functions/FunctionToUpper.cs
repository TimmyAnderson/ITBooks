using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyAzureFunctions
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class FunctionToUpper
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<FunctionToUpper>				MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public FunctionToUpper(ILogger<FunctionToUpper> Logger)
		{
			MLogger=Logger;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[Function("ToUpper")]
		public async Task<IActionResult> Run([HttpTrigger(AuthorizationLevel.Anonymous,"post")] HttpRequest Request)
		{
			MLogger.LogInformation("HTTP FUNCTION [TO UPPER] CALLED.");

			try
			{
				CName											InputName=await Request.ReadFromJsonAsync<CName>();
				CName											OutputName=new CName(InputName.FirstName.ToUpper(),InputName.LastName.ToUpper(),InputName.Age);

				IActionResult									Result=new OkObjectResult(OutputName);

				return(Result);
			}
			catch(Exception E)
			{
				MLogger.LogInformation($"EXCEPTION [{E.Message}].");

				IActionResult									Result=new BadRequestObjectResult("Invalid OBJECT.");

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------