using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! CONTROLLER je vyuzivany EXCEPTION HANDLER MIDDLEWARE COMPONENT na generovanie PROBLEM DETAILS pri vzniku UNHANDLED EXCEPTIONS.
	[ApiController]
	[Route("[controller]")]
	// !!! CONTROLLER nebude zobrazeny vo SWAGGER.
	[ApiExplorerSettings(IgnoreApi=true)]
	public class MyErrorHandlerController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		private readonly ILogger<MyErrorHandlerController>		MLogger;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public MyErrorHandlerController(ILogger<MyErrorHandlerController> Logger)
		{
			MLogger=Logger;
		}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(HandleErrorDevelopment))]
		public IActionResult HandleErrorDevelopment([FromServices] IHostEnvironment HostEnvironment)
		{
			if (HostEnvironment.IsDevelopment()==true)
			{
				// !!! Vracia vzniknutu UNHANDLED EXCEPTION.
				IExceptionHandlerFeature						ExceptionHandlerFeature=HttpContext.Features.Get<IExceptionHandlerFeature>();
				Exception										Exception=ExceptionHandlerFeature.Error;
				string											Path=ExceptionHandlerFeature.Path;

				MLogger.LogError(Exception,"UNHANDLED EXCEPTION DETECTED !");

				if (Path!="/UnhandledExceptions/ThrowUnhandledException")
				{
					IActionResult								Result=Problem(Exception.StackTrace,null,null,Exception.Message);

					return(Result);
				}
				// !!! Umselne sa hodi EXCEPTION, aby sa demonstroval DEFAULT BEHAVIOR ASP.NET pri vniku UNHANDLED EXCEPTIONS.
				else
				{
					throw(Exception);
				}
			}
			else
			{
				IActionResult									Result=NotFound();

				return(Result);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		[HttpGet(nameof(HandleErrorProduction))]
		public IActionResult HandleErrorProduction()
		{
			// !!! Vracia vzniknutu UNHANDLED EXCEPTION.
			IExceptionHandlerFeature							ExceptionHandlerFeature=HttpContext.Features.Get<IExceptionHandlerFeature>();
			Exception											Exception=ExceptionHandlerFeature.Error;
			string												Path=ExceptionHandlerFeature.Path;

			MLogger.LogError(Exception,"UNHANDLED EXCEPTION DETECTED !");

			if (Path!="/UnhandledExceptions/ThrowUnhandledException")
			{
				IActionResult									Result=Problem("UNHANDLED EXCEPTION DETECTED !");

				return(Result);
			}
			// !!! Umselne sa hodi EXCEPTION, aby sa demonstroval DEFAULT BEHAVIOR ASP.NET pri vniku UNHANDLED EXCEPTIONS.
			else
			{
				throw(Exception);
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------