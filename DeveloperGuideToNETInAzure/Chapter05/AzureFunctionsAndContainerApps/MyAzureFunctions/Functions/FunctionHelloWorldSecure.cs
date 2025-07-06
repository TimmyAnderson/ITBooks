using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Functions.Worker;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyAzureFunctions
{
//----------------------------------------------------------------------------------------------------------------------
	public sealed class FunctionHelloWorldSecure
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<FunctionHelloWorldSecure>		MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public FunctionHelloWorldSecure(ILogger<FunctionHelloWorldSecure> Logger)
		{
			MLogger=Logger;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		// !!! ATTRIBUTE [Function] prideluje nazov AZURE FUNCTION.
		[Function("HelloWorldSecure")]
		// !!! ATTRIBUTE [HttpTrigger] v ENUM [AuthorizationLevel] urcuje AUTHORIZATION LEVEL pre AZURE FUNCTION.
		public IActionResult Run([HttpTrigger(AuthorizationLevel.Function,"get")] HttpRequest Request)
		{
			MLogger.LogInformation("HTTP FUNCTION [HELLO WORLD SECURE] CALLED.");

			IActionResult										Result=new OkObjectResult("Hello AZURE FUNCTIONS.");

			return(Result);
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------