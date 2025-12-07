using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNetCore.Mvc;
//----------------------------------------------------------------------------------------------------------------------
namespace MyWebProject
{
//----------------------------------------------------------------------------------------------------------------------
	[ApiController]
	[Route("[controller]")]
	public class UnhandledExceptionsController : ControllerBase
	{
//----------------------------------------------------------------------------------------------------------------------
		// !!! Generovana UNAHDNLED EXCEPTION je UMYSELNE ignorovana v EXCEPTION HANDLER MIDDLEWARE COMPONENT, aby sa ukazal DEFAULT BEHAVIOR ASP.NET.
		[HttpGet(nameof(ThrowUnhandledException))]
		public IActionResult ThrowUnhandledException(int Parameter)
		{
			if (Parameter==1)
			{
				string											Content="Hello WORLD !";
				IActionResult									Result=Ok(Content);

				return(Result);
			}
			else
			{
				throw(new InvalidOperationException("Something BAD HAPPENED."));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
		// !!! UNAHDLED EXCEPTION je zachytena EXCEPTION HANDLER MIDDLEWARE COMPONENT.
		[HttpGet(nameof(ThrowHandledException))]
		public IActionResult ThrowHandledException(int Parameter)
		{
			if (Parameter==1)
			{
				string											Content="Hello WORLD !";
				IActionResult									Result=Ok(Content);

				return(Result);
			}
			else
			{
				throw(new InvalidOperationException("Something BAD HAPPENED."));
			}
		}
//----------------------------------------------------------------------------------------------------------------------
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------